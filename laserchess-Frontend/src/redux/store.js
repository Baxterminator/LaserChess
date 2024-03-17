import { configureStore, applyMiddleware } from "@reduxjs/toolkit";
import gameReducer from "./slices/gameSlice";
import websocketMiddleware from "./slices/websocketMiddleware.js";

const store = configureStore(
    {
        reducer: {
            game: gameReducer,
        },
        middleware: (getDefaultMiddleware) =>
        getDefaultMiddleware().concat(websocketMiddleware),
    }
);

export default store;