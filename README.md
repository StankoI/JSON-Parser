This project is a JSON Parser developed in C++ using Object-Oriented Programming (OOP) principles. It is designed as part of an academic course to demonstrate the practical application of OOP concepts like encapsulation, inheritance, polymorphism, and abstraction.

Key Features:
JSON Parsing: Reads and interprets JSON data structures (objects, arrays, strings, numbers, booleans, and null).
Object-Oriented Design: Modular components such as JsonValue, JsonObject, and JsonArray for clean code organization and scalability.
Error Handling: Detects and reports syntax errors in JSON files.
Extensibility: Easily extendable to support custom data types or additional features.
File I/O Support: Reads JSON data from files and can output formatted data.
Project Structure:
JsonParser: Main class responsible for parsing raw JSON strings into structured objects.
JsonValue: Abstract base class representing any JSON value.
JsonObject: Handles JSON objects ({}) using key-value pairs.
JsonArray: Manages JSON arrays ([]).
JsonString, JsonNumber, JsonBoolean, JsonNull: Represent primitive JSON data types.
