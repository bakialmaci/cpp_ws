/*
std::decay_t is a type transformation utility provided by the C++ Standard Library that can be used to simplify types for type checking and manipulation.
std::decay_t<T> performs the following transformations:
    - Removes references (i.e., T& becomes T).
    - Removes const/volatile qualifiers (i.e., const T becomes T).
    - Converts array types into pointers (i.e., T[] becomes T*).
    - Converts function types into function pointers (i.e., void() becomes void(*)()).
*/

#include <iostream>
#include <variant>

// Define the states of the state machine
struct StartState {};
struct RunningState { int speed; };
struct StoppedState {};

class StateMachine {
public:
    // Define the state machine as a variant of the possible states
    using State = std::variant<StartState, RunningState, StoppedState>;
    // Store the current state of the state machine
    State currentState;
    // Initialize the state machine with the Start state
    StateMachine() : currentState(StartState{}) {}

    // Transition to the Running state with a given speed
    void transitionToRunning(int speed) {
        currentState = RunningState{speed};
    }

    // Transition to the Stopped state
    void transitionToStopped() {
        currentState = StoppedState{};
    }

    // Print the current state of the state machine
    // printState method marked as const, which means it does not modify the object's state.
    void printState() const {
        // Use std::visit to apply a lambda function to the current state.
        std::visit([](const auto& state) {
            // Use decltype to get the type of the state variable.
            // Use std::decay_t to remove any reference or const qualifiers from the type of the state.
            // Use std::is_same_v to check if the type of the state is the same as one of the state types.
            using T = std::decay_t<decltype(state)>;
            /*
                We can't use decltype without std::decay_t because decltype will return a reference type for the state variable,
                which will not match the types of the states (e.g., RunningState vs. RunningState&).
                std::decay_t removes any reference or const qualifiers from the type, allowing us to compare it with the state types.
                using T = decltype(state); // Error: T is a reference type (e.g., RunningState&)
            */
            if constexpr (std::is_same_v<T, StartState>) {
                std::cout << "State: Start" << std::endl;
            } else if constexpr (std::is_same_v<T, RunningState>) {
                std::cout << "State: Running at speed " << state.speed << std::endl;
            } else if constexpr (std::is_same_v<T, StoppedState>) {
                std::cout << "State: Stopped" << std::endl;
            }
        }, currentState);
    }
};

int main() {
    StateMachine machine;
    machine.printState();

    machine.transitionToRunning(50);
    machine.printState();

    machine.transitionToStopped();
    machine.printState();

    return 0;
}
