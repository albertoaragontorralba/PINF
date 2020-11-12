# Obtenemos mensaje a cifrar desde el usuario
# llamamos a upper para obtener sólo mayúsculas
texto = input("Mensaje > ").upper()

# Pedimos al usuario la cantidad de desplazamiento
n = 3

# Abecedario a utilizar en el cifrado
abc = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ123456789"

# Variable para guardar mensaje cifrado
cifrado = ""

# Iteramos por cada letra del mensaje
for l in texto:
    # Si la letra está en el abecedario se reemplaza
    if l in abc:
        pos_letra = abc.index(l)
        # Sumamos para movernos a la derecha del abc
        nueva_pos = (pos_letra + n) % len(abc)
        cifrado+= abc[nueva_pos]
    else:
        # Si no está en el abecedario sólo añadelo
        cifrado+= l

print("Mensaje cifrado:", cifrado)



for i in range(28):
    # Guardar posible mensaje
    descifrado = ""
    for l in texto:
        # Si la letra está en el abecedario reemplazamos
        if l in abc:
            pos_letra = abc.index(l)
            # Restamos para movernos a la izquierda
            nueva_pos = (pos_letra - i) % len(abc)
            descifrado += abc[nueva_pos]
        else:
            descifrado+= l
    msj = (f"ROT-{i}:", descifrado)
    print(msj)