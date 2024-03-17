import io from "socket.io-client";
import { applyMovement } from "./gameSlice";

const SERVER_URL = "http://your-server-url"; // Replace this with your server URL

const socketMiddleware = () => {
  const socket = io(SERVER_URL);

  // Connect to the server
  socket.on("connect", () => {
    console.log("Connected to server");
  });

  // Listen for messages from the server and dispatch corresponding actions
  socket.on("movementResponse", (data) => {
    // Dispatch an action to handle received movement data
    applyMovement(data); // Assuming data received from server contains movement info
  });

  // Return the middleware function
  return ({ dispatch }) => (next) => (action) => {
    if (action.type === "SEND_MOVEMENT") {
      // If the action type is "SEND_MOVEMENT", send movement data to the server
      socket.emit("movementRequest", action.payload);
      console.log("working", action.payload);
    } else {
      // Pass all other actions through to the next middleware
      return next(action);
    }
  };
};

export default socketMiddleware;
