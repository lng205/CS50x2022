import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total = cash
    for stock in stocks:
        stock_data = lookup(stock["symbol"])
        stock["name"], stock["price"] = stock_data["name"], stock_data["price"]
        stock["sum"] = stock["share"] * stock["price"]
        total += stock["sum"]
    return render_template("home.html", stocks=stocks, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST
    if request.method == "POST":
        # Get user input
        symbol = request.form.get("symbol")
        share = request.form.get("shares")

        # Validate the submission
        if not symbol:
            # flash("Please enter a symbol.")
            # return redirect("/buy")
            return apology("Please enter a symbol.")
        if not share:
            # flash("Please enter a share.")
            # return redirect("/buy")
            return apology("Please enter a share.")
        if not share.isdigit():
            return apology("Please enter a positive integer share.")
        share = int(share)
        if share <= 0:
            # flash("Please enter a positive integer share.")
            # return redirect("/buy")
            return apology("Please enter a positive integer share.")

        # Look up the symbol
        symbol_data = lookup(symbol)
        if not symbol_data:
            # flash("Invalid symbol.")
            # return redirect("/buy")
            return apology("Invalid symbol.")
        price = symbol_data["price"]

        # Get current share and cash
        row = db.execute("SELECT share FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        if row:
            share_old = row[0]["share"]
        else:
            share_old = 0
        cash_old = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Calculate share and cash after purchase
        cost = share * price
        share_new = share_old + share
        cash_new = cash_old - cost

        # Check for cash's sufficiency
        if cash_new < 0:
            # flash(f"Insufficient cash. Current cash: {usd(cash_old)}. Cash required: {usd(cost)}")
            # return redirect("/buy")
            return apology(f"Insufficient cash. Current cash: {usd(cash_old)}. Cash required: {usd(cost)}")

        # Update users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_new, session["user_id"])

        # Update stocks table
        if share_old == 0:
            db.execute("INSERT INTO stocks VALUES(?, ?, ?)", session["user_id"], symbol, share_new)
        else:
            db.execute("UPDATE stocks SET share = ? WHERE user_id = ? AND symbol = ?", share_new, session["user_id"], symbol)

        # Update history table
        db.execute("Insert INTO history(user_id, symbol, price, share) VALUES(?, ?, ?, ?)",
                   session["user_id"], symbol, price, share)

        # Success flash
        flash(
            f"Success! Total cost:{usd(cost)}. Current Shares of {symbol_data['name']}: {share_new}. Current Cash: {usd(cash_new)}")
        return redirect("/buy")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            # flash("must provide username")
            # return redirect("/login")
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            # flash("must provide password")
            # return redirect("/login")
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            # flash("invalid username and/or password")
            # return redirect("/login")
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST
    if request.method == "POST":
        price = lookup(request.form.get("symbol"))
        if price:
            flash(f"A share of {price['name']}({price['symbol']}) costs {usd(price['price'])}.")
            return redirect("/quote")
        else:
            # flash
            # redirect
            return apology("Invalid symbol.")

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validate the submission
        if not username:
            # flash("must provide username")
            # return redirect("/register")
            return apology("must provide username.")
        elif not password:
            # flash("must provide password")
            # return redirect("/register")
            return apology("must provide password.")
        elif password != confirmation:
            return apology("password not match.")

        namesRegisterd = [nameRegisterd['username'] for nameRegisterd in db.execute("SELECT username FROM users")]
        if username in namesRegisterd:
            # flash("Username has already been registered.")
            # return redirect('/register')
            return apology("Username has already been registered.")

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))
        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # User reached route via POST
    if request.method == "POST":
        # Get user input
        symbol = request.form.get("symbol")
        share = request.form.get("shares")

        # Validate the submission
        if not symbol:
            # flash("Please choose an option.")
            # return redirect("/sell")
            return apology("Please choose an option.")
        if not share:
            # flash("Please enter a share.")
            # return redirect("/sell")
            return apology()
        share = - int(share)
        if share >= 0:
            # flash("Please enter a positive integer Share.")
            # return redirect("/sell")
            return apology("Please enter a positive integer Share.")

        # Look up the symbol
        symbol_data = lookup(symbol)
        if not symbol_data:
            # flash("Invalid symbol.")
            # return redirect("/sell")
            return apology("Invalid symbol.")
        price = symbol_data["price"]

        # Get current share and cash
        share_old = db.execute("SELECT share FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]["share"]
        cash_old = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Calculate share and cash after selling
        share_new = share_old + share
        cash_new = cash_old - share * price

        # Check for share's sufficiency
        if share_new < 0:
            # flash(f"Insufficient share. Current share: {share_old}")
            # return redirect("/sell")
            return apology(f"Insufficient share. Current share: {share_old}")

        # Update users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_new, session["user_id"])

        # Update stocks table
        if share_new == 0:
            db.execute("DELETE FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        else:
            db.execute("UPDATE stocks SET share = ? WHERE user_id = ? AND symbol = ?", share_new, session["user_id"], symbol)

        # Update history table
        db.execute("Insert INTO history(user_id, symbol, price, share) VALUES(?, ?, ?, ?)",
                   session["user_id"], symbol, price, share)

        # Success flash
        flash(
            f"Success! Total earn:{usd(share * price)}. Current shares of {symbol_data['name']}: {share_new}. Current cash: {usd(cash_new)}")
        return redirect("/sell")

    symbols = db.execute("SELECT symbol FROM STOCKS WHERE user_id = ?", session["user_id"])
    return render_template("sell.html", symbols=symbols)
