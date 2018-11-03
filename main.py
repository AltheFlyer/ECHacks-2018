from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
@app.route('/intro')
def index():
    return "HELLO WORLD!"

#@app.route("/static/<string:s>")
#def nope(s="no"):
#    return "Very clever..."