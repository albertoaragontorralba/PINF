from flask import Flask, render_template, request, redirect, url_for, flash
from flask_mysqldb import MySQL

from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'flask'
mysql = MySQL(app)
mysql.init_app(app)

@app.route('/') #RUTA PRINCIPAL
def Index():
    return render_template('index.html')

@app.route('/registrarse') #RUTA REGISTRARSE
def registrarse():
    return render_template('registrarse.html')

@app.route('/registrarse/obtener_datos', methods =['POST'])
def obtener_datos():
    if request.method == 'POST':
        Nombre = request.form["Nombre"]
        Email = request.form["Email"]
        Contraseña = request.form["Contraseña"]

        cur = mysql.connection.cursor()

        cur.execute('INSERT INTO usuario (usuario, email, contraseña) VALUES (%s, %s, %s)',(Nombre, Email, Contraseña))
        r = cur.fetchone()
        cur.close()
        if r is None:
            mysql.connection.commit()
            flash('Cuenta creada correctamente', "success")
        else:
            flash('Este correo ya ha sido utilizado', "warning")
            return redirect(url_for('registrarse'))


    return redirect(url_for('Index'))


@app.route('/Olvidar_contrasena')
def olvidar_contrasena():
    return render_template('olvidar_contrasena.html')

@app.route("/login", methods=['POST'])
def login():
    if request.method == 'POST':
        Email = request.form["email"]
        Contraseña = request.form["password"]
        print(Email, Contraseña)
        cur = mysql.connection.cursor()
        cur.execute("Select usuario from usuario where email = '" + Email + "'and contraseña = '" + Contraseña + "'")
        r = cur.fetchone()
        cur.close()
        if r is None:
            flash("Credenciales incorrectas", "warning")
            return redirect(url_for('Index'))
        else:
            flash("Sesion iniciada", "success")
            return redirect(url_for('inside'))
    else:
        return render_template('index.html')

@app.route("/login/inside")
def inside():
    return render_template('login.html')

def cifrar(texto):
    abc = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ123456789"
    cifrado = ""
    # Iteramos por cada letra del mensaje
    for l in texto:
        # Si la letra está en el abecedario se reemplaza
        if l in abc:
            pos_letra = abc.index(l)
            # Sumamos para movernos a la derecha del abc
            nueva_pos = (pos_letra + 17) % len(abc)
            cifrado += abc[nueva_pos]
        else:
            # Si no está en el abecedario sólo añadelo
            cifrado += l

    print("Mensaje cifrado:", cifrado)
    return cifrado

if __name__ == '__main__':
    app.secret_key = 'super secret key'
    app.config['SESSION_TYPE'] = 'filesystem'
    app.run(port=3000, debug=True)