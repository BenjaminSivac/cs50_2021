-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description -- A look at the crime scene
FROM crime_scene_reports
WHERE year = 2020
AND month = 7
AND day = 28
AND street = "Chamberlin Street"; 

SELECT transcript -- Check the interviews from the 3 witnesses
FROM interviews
WHERE year = 2020
AND month = 7
AND day = 28; -- We found 3 useful threads to follow: The thief withdrew money form the ATM, Was on a call with an accomplice, and had planned a fight the next day. 

SELECT people.name -- We begin by looking up the names of people who left the courthouse.
FROM people
JOIN courthouse_security_logs
ON people.license_plate = courthouse_security_logs.license_plate
WHERE day = 28
AND month = 7
AND year = 2020
AND hour = 10
AND minute >= 15
AND minute < 25
AND activity = "exit"; -- 8 people

SELECT DISTINCT(name) -- Next, We look at how many people withdrew money from the ATM
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE day = 28
AND month = 7
AND year = 2020
AND transaction_type = "withdraw"
AND atm_location = "Fifer Street";

SELECT DISTINCT(name) -- Check for names of passengers on the flight according to the description.
FROM people
JOIN passengers on people.passport_number = passengers.passport_number
WHERE flight_id = (
SELECT ID
FROM flights
WHERE year = 2020
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1);

SELECT DISTINCT(name) -- Check for people who had a short phonecall around the same time of the crimescene.
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60;

--- Intersect all queries to check for the person who's linked to the crime
SELECT people.name
FROM people
JOIN courthouse_security_logs
ON people.license_plate = courthouse_security_logs.license_plate
WHERE day = 28
AND month = 7
AND year = 2020
AND hour = 10
AND minute >= 15
AND minute < 25
AND activity = "exit"

INTERSECT

SELECT DISTINCT(name)
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE day = 28
AND month = 7
AND year = 2020
AND transaction_type = "withdraw"
AND atm_location = "Fifer Street"

INTERSECT

SELECT DISTINCT(name)
FROM people
JOIN passengers 
ON people.passport_number = passengers.passport_number
WHERE flight_id = (
SELECT ID
FROM flights
WHERE year = 2020
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1)

INTERSECT

SELECT DISTINCT(name)
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60; -- Ernest !

SELECT city FROM airports -- Check for the flight destination.
WHERE id = (
SELECT destination_airport_id 
FROM flights
WHERE day = 29
AND month = 7
AND year = 2020
ORDER BY hour, minute
LIMIT 1);

SELECT name -- Check for who he was on the phone with (his accomplice)
FROM people 
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE day = 28
AND year = 2020
AND month = 7
AND duration < 60
AND caller = (
SELECT phone_number 
FROM people 
WHERE name = "Ernest");





