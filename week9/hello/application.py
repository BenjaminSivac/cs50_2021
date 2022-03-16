from flask import Flask, render_template, request

app = Flask(__name__) # turn the current file into an application. A web application that will listen to browser's requests.

@app.route("/", methods=["GET", "POST"]) #@ is a python decorater. Applying function to another. Defined route.
def index():
    if request.method == "GET":
        return render_template("index.html") 
    if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name", "world"))
    
    
