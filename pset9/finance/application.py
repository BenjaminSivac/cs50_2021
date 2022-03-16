import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    
    stocks = db.execute(
        "SELECT symbol, name, price, SUM(shares) AS totalShares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    
    total = cash
    
    for stock in stocks:
        total += stock["price"] * stock["totalShares"]
    
    return render_template("index.html", stocks=stocks, cash=cash, total=total, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("must provide symbol", 403)
        
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid symbol")
        
        shares = request.form.get("shares")
        try:
            shares = int(shares)
        except:
            return apology("must be an integer")
        
        if shares <= 0:
            return apology("must be positive")
            
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        
        stock_name = stock["name"]
        stock_price = stock["price"]
        tot_price = stock_price * shares
        
        if tot_price > cash:
            return apology("not enough cash", 403)
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - tot_price, user_id)
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ? , ?)",
                        user_id, stock_name, shares, stock_price, 'buy', symbol)
        flash("Purchase successful!")   
        return redirect('/')
        
    else:
        return render_template("buy.html")
    

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    
    history = db.execute("SELECT symbol, type, shares, price, time FROM transactions WHERE user_id = ?", user_id)
    
    return render_template("history.html", history=history, usd=usd)


@app.route("/change_pw", methods=["GET", "POST"])
@login_required
def change_pw():
    """Chance password"""
    user_id = session["user_id"]
    
    if request.method == "POST":

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        # Ensure username was submitted
        if not password:
            return apology("must provide old password", 403)

        # Ensure password confirmation
        elif not confirmation:
            return apology("must provide password once more", 403)

        elif password != confirmation:
            return apology("passwords do not match", 403)
        
        hash = generate_password_hash(password)
        # Query database for username
        
        db.execute("UPDATE users SET hash = ? WHERE id = ?", hash, user_id)
        flash("Password change successful!")
        return redirect('/')
        
    else:
        return render_template("change_pw.html")
    

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        
        if not symbol:
            return apology("must provide symbol")
        
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid symbol")
        
        return render_template("quoted.html", stock=stock, usd=usd)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()
    
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        
        # Ensure username was submitted
        if not username:
            return apology("must provide username")

        # Ensure password was submitted
        elif not password:
            return apology("must provide password")
        
        # Ensure password confirmation
        elif not confirmation:
            return apology("must provide password once more")

        if password != confirmation:
            return apology("passwords do not match")
        
        hash = generate_password_hash(password)
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        
        if len(rows) == 1:
            return apology("username taken")
        else:
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", username, hash)
            flash("Registration successful!")
            return redirect('/')
           
    else:
        return render_template("register.html")
    

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", symbols=symbols)
        
    else:
        symbol = request.form.get("symbol")
        
        shares = request.form.get("shares")
        try:
            shares = int(shares)
        except:
            return apology("must be an integer")
        if shares <= 0:
            return apology("must be positive")
        
        stock_price = lookup(symbol)["price"]
        stock_name = lookup(symbol)["name"]
        
        shares_owned = db.execute("SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ?",
                                  user_id, symbol)[0]["SUM(shares)"]
        if shares_owned < shares:
            return apology("Not enough shares")
        
        cash_owned = db.execute("SELECT cash from users WHERE id = ?", user_id)[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_owned + stock_price * shares, user_id)
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)", 
                user_id, stock_name, -shares, stock_price, "sell", symbol)
        flash("Transaction successful!")
        return redirect("/")
        
        
def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
