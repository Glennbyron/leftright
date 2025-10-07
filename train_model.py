import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

# This will load the data
data = pd.read_csv("responses.csv")

# Party numbers
party_names = {"Democrat": 0, "Republican": 1, "Libertarian": 2, "Green": 3, "Unknown": 4}
data["UserLabel"] = data["UserLabel"].map(party_names)

# Feat and tar
X = data[["Democrat", "Republican", "Libertarian", "Green"]]
y = data["UserLabel"]

# Split into training and testing things
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

# Make and train it
model = RandomForestClassifier()
model.fit(X_train, y_train)

# testy test
predictions = model.predict(X_test)

# How we doing?
acc = accuracy_score(y_test, predictions)
prec = precision_score(y_test, predictions, average="weighted", zero_division=0)
rec = recall_score(y_test, predictions, average="weighted", zero_division=0)
f1 = f1_score(y_test, predictions, average="weighted", zero_division=0)

# Printing
print("How good is the model?")
print("Quize Accuracy:", round(acc, 2))
print("Quize Precision:", round(prec, 2))
print("Quize Recall:", round(rec, 2))
print("Quize F1 Score:", round(f1, 2))