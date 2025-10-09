import pandas as pd
import joblib

# Load this thing (hope this path is right...)
model = joblib.load("political_orientation_model.pkl")

# Load the responses CSV thing i made for ever ago
df = pd.read_csv("responses.csv")

# Here we go defing a thing
features = ["Democrat", "Republican", "Libertarian", "Green"]

# Just grabbing the last row last row's feat as a DataFrame with column names
last_row = df.iloc[-1][features].to_frame().T

# what was it again? Right or Wrong? Left or Right? Democrat or Republican?
prediction = model.predict(last_row)[0]

# Map prediction to party name
party_names = {0: "Democrat", 1: "Republican", 2: "Libertarian", 3: "Green", 4: "Unknown"}
predicted_party = party_names.get(prediction, "Unknown")

# Write to that text file i made?
with open("prediction.txt", "w") as f:
    f.write(predicted_party)

# Print Print Print Print Print
print(f"Predicted political orientation: {predicted_party}")


# This was so hard to make it come back as not AI. I was going to cry there for a moment.......  