jl=[]
print(jl)
heroe={"nombre":"superman","poder":"volar","origen":"kripton"}
jl.append(heroe)
print (jl)
heroe={"nombre":"batman","poder":"N/A","origen":"tierra"}
jl.append(heroe)
print (jl)
heroe={"nombre":"wonder woman","poder":"super fuerza","origen":"tierra"}
jl.append(heroe)
print (jl)
print()

print(jl[0]["nombre"])
print(jl[2]["poder"])
print(jl[1]["origen"])
print()

#pies a pulgadas,yardas,millas y metros
ft= float(input("ingrese el valor en pies "))
inch=12*ft
yd=ft/3
mi=ft/5280
m=0.3048*ft
print(ft," pies en pulgadas equivale a ", inch)
print(ft," pies en yardas equivale a ", yd)
print(ft," pies en millas equivale a ", mi)
print(ft," pies en metros equivale a ", m)
print(".>")

b= float(input("radio en metros "))

dia = 2*b
area= 3.1416*b*2
print("el diametro vale ",dia)
print("el area vale ",area)
print(".>")