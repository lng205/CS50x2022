num = int(input("Number: "))

digit, counter, sum = 0, 0, 0
while (num > 0):
    counter += 1
    digitbuf = digit
    digit = num % 10
    if counter % 2 == 0:
        sum += (2 * digit) % 10 + (2 * digit) // 10
    else:
        sum += digit
    num = num // 10

cardtype = "INVALID"
if sum % 10 == 0:
    if digit == 3 and counter == 15 and (digitbuf == 4 or digitbuf == 7):
        cardtype = "AMEX"
    elif digit == 4 and (counter == 13 or counter == 16):
        cardtype = "VISA"
    elif digit == 5 and counter == 16 and (digitbuf > 0 and digitbuf < 6):
        cardtype = "MASTERCARD"
print(cardtype)