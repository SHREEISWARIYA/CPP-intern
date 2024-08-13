#include <iostream>
#include <stack>
#include <stdexcept> // For std::runtime_error

class QueueUsingStacks {
private:
    std::stack<int> stack1; // Stack for enqueue operations
    std::stack<int> stack2; // Stack for dequeue operations

    // Transfer all elements from stack1 to stack2
    void transfer() {
        while (!stack1.empty()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }

public:
    // Enqueue operation: push to stack1
    void enqueue(int value) {
        stack1.push(value);
    }

    // Dequeue operation: pop from stack2
    int dequeue() {
        if (stack2.empty()) {
            transfer(); // Transfer elements if stack2 is empty
        }
        if (stack2.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        int value = stack2.top(); 
        stack2.pop();
        return value;
    }

    // Display elements in the queue
    void display() const {
        std::stack<int> tempStack1 = stack1;
        std::stack<int> tempStack2 = stack2;
        std::stack<int> displayStack;

        // Transfer elements from stack2 to displayStack
        while (!tempStack2.empty()) {
            displayStack.push(tempStack2.top());
            tempStack2.pop();
        }

        // Transfer elements from stack1 to displayStack
        while (!tempStack1.empty()) {
            displayStack.push(tempStack1.top());
            tempStack1.pop();
        }

        // Print elements in displayStack
        while (!displayStack.empty()) {
            std::cout << displayStack.top() << " ";
            displayStack.pop();
        }
        std::cout << std::endl;
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return stack1.empty() && stack2.empty();
    }
};

// Main function with menu
int main() {
    QueueUsingStacks queue;
    int choice, value;

    while (true) {
        std::cout << "\nChoose an operation:\n";
        std::cout << "1. Enqueue\n";
        std::cout << "2. Dequeue\n";
        std::cout << "3. Display\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value to enqueue: ";
                std::cin >> value;
                queue.enqueue(value);
                std::cout << "Enqueued " << value << std::endl;
                break;

            case 2:
                try {
                    value = queue.dequeue();
                    std::cout << "Dequeued " << value << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 3:
                if (queue.isEmpty()) {
                    std::cout << "Queue is empty" << std::endl;
                } else {
                    std::cout << "Queue contents: ";
                    queue.display();
                }
                break;

            case 4:
                std::cout << "Exiting...\n";
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}