nome = "valentina"
cognome = "piscopo"
completo = f"\t{nome} {cognome}"
print(completo.lower())
print(completo.upper())
print(completo.title())

tit = f"{completo.title()}"

msg = f"Ciao {nome} {cognome}, benvenuta nella tua Home!"
msg2 = f"\t\tCiao {tit}, benvenuta nella tua home!"

print(msg)
print(msg2)