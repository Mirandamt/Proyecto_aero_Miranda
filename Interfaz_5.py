import tkinter as tk
from tkinter import messagebox
import matplotlib.pyplot as plt

# Listas para almacenar los datos
latitudes = []
longitudes = []

def agregar_datos(latitud, longitud):
    """Agrega los datos de latitud y longitud a las listas."""
    latitudes.append(latitud)
    longitudes.append(longitud)
    messagebox.showinfo("Datos Agregados", f"Latitud: {latitud}, Longitud: {longitud}")

def graficar_datos():
    """Grafica los datos almacenados."""
    if not latitudes or not longitudes:
        messagebox.showwarning("Advertencia", "No hay datos para graficar.")
        return

    plt.figure(figsize=(10, 6))
    plt.scatter(longitudes, latitudes, color='blue', marker='o')
    plt.title("Gráfico de Latitud y Longitud")
    plt.xlabel("Longitud")
    plt.ylabel("Latitud")
    plt.grid()
    plt.show()

# Crear la ventana principal
ventana = tk.Tk()
ventana.title("Interfaz de Datos GPS")

# Etiquetas y botones
tk.Label(ventana, text="Ingrese la Latitud:").pack(pady=5)
latitud_entry = tk.Entry(ventana)
latitud_entry.pack(pady=5)

tk.Label(ventana, text="Ingrese la Longitud:").pack(pady=5)
longitud_entry = tk.Entry(ventana)
longitud_entry.pack(pady=5)

tk.Button(ventana, text="Agregar Datos", command=lambda: agregar_datos(float(latitud_entry.get()), float(longitud_entry.get()))).pack(pady=10)
tk.Button(ventana, text="Graficar Datos", command=graficar_datos).pack(pady=10)

# Ejecutar la aplicación
ventana.mainloop()
