import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
import datetime

data = pd.read_json('generated_temperature_data_with_constraints.json', lines=True)

df = pd.DataFrame(data)

# Conversion des timestamps en datetime
df['timestamp'] = pd.to_datetime(df['timestamp'])

# Conversion des timestamps en secondes depuis l'époque Unix
df['timestamp'] = df['timestamp'].apply(lambda x: x.timestamp())

# Séparation des caractéristiques et de la cible
X = df[['timestamp', 'peopleCount', 'outTemperature']]
y = df['temperature']
ybis = df['noise']

# Division en ensembles d'entraînement et de test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
X_train2, X_test2, y_train2, y_test2 = train_test_split(X, ybis, test_size=0.2, random_state=42)

# Création et entraînement du modèle
model = LinearRegression()
model2 = LinearRegression()

model.fit(X_train, y_train)
model2.fit(X_train2, y_train2)


# Prédiction et évaluation
predictions = model.predict(X_test)
predictions2 = model.predict(X_test2)

mse = mean_squared_error(y_test, predictions)
mse2 = mean_squared_error(y_test2, predictions2)

print(f"Erreur quadratique moyenne : {mse}")
print(f"Erreur quadratique moyenne : {mse2}")

# Prédiction pour une nouvelle date
new_date = pd.to_datetime('2023-12-19T12:00:00')
new_timestamp = new_date.timestamp()
new_people_count = 8  # Remplacez par la valeur appropriée
new_out_temperature = 19  # Remplacez par la valeur appropriée

# Création du DataFrame pour la prédiction
df_new = pd.DataFrame({
    'timestamp': [new_timestamp],
    'peopleCount': [new_people_count],
    'outTemperature': [new_out_temperature]
})

# Utiliser le modèle pour prédire
predicted_temp = model.predict(df_new)
predicted_temp2 = model2.predict(df_new)

print(f"Température prédite pour le {new_date} : {predicted_temp[0]}")
print(f"Bruit prédit pour le {new_date} : {predicted_temp2[0]}")
