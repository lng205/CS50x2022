-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Extract the id, street and description of the crime based on the time. The id 295's description corresponds to the crime:
/*"Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Interviews were conducted today with three witnesses who were present at the time –each of their interview transcripts mentions the bakery."*/
SELECT id, description, street
  FROM crime_scene_reports
 WHERE year = 2021
   AND month = 7
   AND day = 28;

-- Extract the imformation of the interview of the crime based on the reference of "bakery":
/* +---------+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|  name   |                                                                                                                                                     transcript                       |
+---------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |

| Eugene  | I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                              |

| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket.                                                                                                     |
+---------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+*/
SELECT name, transcript
  FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND transcript LIKE "%bakery%";

-- Get the flight number and destination id
/*+----+------------------------+
| id | destination_airport_id |
+----+------------------------+
| 36 | 4                      |
+----+------------------------+*/
SELECT id, destination_airport_id
  FROM flights
 WHERE year = 2021
   AND month = 7
   AND day = 28 + 1
   ORDER BY hour ASC, minute ASC LIMIT 1;

-- Match the theif based on bank acount, license plate, passport number and phone call
/*+--------+-------+----------------+
|   id   | name  |  phone_number  |
+--------+-------+----------------+
| 686048 | Bruce | (367) 555-5533 |
+--------+-------+----------------+*/
SELECT id, name, phone_number
  FROM people
 WHERE id IN
       (SELECT person_id
          FROM bank_accounts
         WHERE account_number IN
               (SELECT account_number
                  FROM atm_transactions
                 WHERE year = 2021
                   AND month = 7
                   AND day = 28
                   AND atm_location = "Leggett Street"
                   AND transaction_type = "withdraw"))
   AND license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND hour = 10
           AND minute > 15
           AND minute <= 15 + 10
           AND activity = "exit")
   AND passport_number IN
       (SELECT passport_number
          FROM passengers
         WHERE flight_id = 36)
   AND phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND duration <= 60);

-- Find the destination of the flight
/*+---------------+
|     city      |
+---------------+
| New York City |
+---------------+*/
SELECT city
  FROM airports
 WHERE id = 4;

 --Find the accomplice
 /*+-------+
| name  |
+-------+
| Robin |
+-------+*/
 SELECT name
   FROM people
  WHERE phone_number =
        (SELECT receiver
           FROM phone_calls
          WHERE caller = "(367) 555-5533"
            AND year = 2021
            AND month = 7
            AND day = 28
            AND duration <= 60);