import React, { useState, useEffect } from "react";

function App() {

  const [isLoggedIn, setIsLoggedIn] = useState(false);
  const [count, setCount] = useState(0);
  const [darkMode, setDarkMode] = useState(false);
  const [feedback, setFeedback] = useState("");

  useEffect(() => {
    console.log("Component Loaded");
  }, []);

  const appStyle = {
    backgroundColor: darkMode ? "#222" : "#f4f4f4",
    color: darkMode ? "#fff" : "#000",
    minHeight: "100vh",
    padding: "40px",
    textAlign: "center",
    transition: "0.3s ease"
  };

  const buttonStyle = {
    margin: "10px",
    padding: "10px 20px",
    cursor: "pointer"
  };

  return (
    <div style={appStyle}>
      <h1>Student Interaction Panel</h1>

      <section>
        <h2>{isLoggedIn ? "User Logged In" : "User Logged Out"}</h2>
        <button
          style={buttonStyle}
          onClick={() => setIsLoggedIn(!isLoggedIn)}
        >
          {isLoggedIn ? "Logout" : "Login"}
        </button>
      </section>

      <hr />

      <section>
        <h2>Total Clicks: {count}</h2>
        <button
          style={buttonStyle}
          onClick={() => setCount(count + 1)}
        >
          Click Me
        </button>
      </section>

      <hr />

      <section>
        <button
          style={buttonStyle}
          onClick={() => setDarkMode(!darkMode)}
        >
          Switch to {darkMode ? "Light" : "Dark"} Theme
        </button>
      </section>

      <hr />

      <section>
        <h2>Feedback</h2>
        <input
          type="text"
          placeholder="Enter your feedback"
          value={feedback}
          onChange={(e) => setFeedback(e.target.value)}
          style={{ padding: "8px", width: "250px" }}
        />
        <p>Live Feedback: {feedback}</p>
      </section>

    </div>
  );
}

export default App;
