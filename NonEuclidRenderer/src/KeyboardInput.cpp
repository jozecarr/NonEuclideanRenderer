#include "KeyboardInput.h"

keyval::keyval(int k, int v) { key = k; val = v; };

KeyboardInput::KeyboardInput() {
    printf("init\n");
    keysDown = {};
    for (int i = 0; i < 5000; i++)
    {
        keysDown.push_back(keyval(i, false));
    }
}

void KeyboardInput::KeyDownEvent(int key) {
    printf("keydown\n");
    printf("%d\n", keysDown.size());

    for (keyval& kv: keysDown) {
        if (kv.key == key) {
            kv.val = true; // Update the key state
            return;
        }
    }
}

void KeyboardInput::KeyUpEvent(int key) {
    // Find the key and mark it as released
    for (keyval& kv : keysDown) {
        if (kv.key == key) {
            kv.val = false; // Update the key state
            return;
        }
    }
}

bool KeyboardInput::IsKeyDown(int key) {
    // Check if the key is pressed
    for (keyval& kv : keysDown) {
        if (kv.key == key && kv.val) {
            return true;
        }
    }
    return false;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods ) {
    printf("calback\n");
    KeyboardInput* input = static_cast<KeyboardInput*>(glfwGetWindowUserPointer(window));
    input = new KeyboardInput();
    
    if (action == GLFW_PRESS) {
        input->KeyDownEvent(key);
    }
    else if (action == GLFW_RELEASE) {
        input->KeyUpEvent(key);
    }
}