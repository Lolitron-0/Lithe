#include "WindowsKeyboard.hpp"
#include "Lithe/Core/Application.hpp"
#include <GLFW/glfw3.h>

namespace Lithe
{
    const std::unordered_map<Keyboard::Key, int> WindowsKeyboard::s_KeyToGlfwMap
    {
            {Keyboard::Key::Unknown,        GLFW_KEY_UNKNOWN       },
            {Keyboard::Key::Space,          GLFW_KEY_SPACE         },
            {Keyboard::Key::Apostrophe,     GLFW_KEY_APOSTROPHE    },
            {Keyboard::Key::Comma,          GLFW_KEY_COMMA         },
            {Keyboard::Key::Minus,          GLFW_KEY_MINUS         },
            {Keyboard::Key::Period,         GLFW_KEY_PERIOD        },
            {Keyboard::Key::Slash,          GLFW_KEY_SLASH         },
            {Keyboard::Key::Key0,           GLFW_KEY_0             },
            {Keyboard::Key::Key1,           GLFW_KEY_1             },
            {Keyboard::Key::Key2,           GLFW_KEY_2             },
            {Keyboard::Key::Key3,           GLFW_KEY_3             },
            {Keyboard::Key::Key4,           GLFW_KEY_4             },
            {Keyboard::Key::Key5,           GLFW_KEY_5             },
            {Keyboard::Key::Key6,           GLFW_KEY_6             },
            {Keyboard::Key::Key7,           GLFW_KEY_7             },
            {Keyboard::Key::Key8,           GLFW_KEY_8             },
            {Keyboard::Key::Key9,           GLFW_KEY_9             },
            {Keyboard::Key::Semicolon,      GLFW_KEY_SEMICOLON     },
            {Keyboard::Key::EQUAL,          GLFW_KEY_EQUAL         },
            {Keyboard::Key::A,              GLFW_KEY_A             },
            {Keyboard::Key::B,              GLFW_KEY_B             },
            {Keyboard::Key::C,              GLFW_KEY_C             },
            {Keyboard::Key::D,              GLFW_KEY_D             },
            {Keyboard::Key::E,              GLFW_KEY_E             },
            {Keyboard::Key::F,              GLFW_KEY_F             },
            {Keyboard::Key::G,              GLFW_KEY_G             },
            {Keyboard::Key::H,              GLFW_KEY_H             },
            {Keyboard::Key::I,              GLFW_KEY_I             },
            {Keyboard::Key::J,              GLFW_KEY_J             },
            {Keyboard::Key::K,              GLFW_KEY_K             },
            {Keyboard::Key::L,              GLFW_KEY_L             },
            {Keyboard::Key::M,              GLFW_KEY_M             },
            {Keyboard::Key::N,              GLFW_KEY_N             },
            {Keyboard::Key::O,              GLFW_KEY_O             },
            {Keyboard::Key::P,              GLFW_KEY_P             },
            {Keyboard::Key::Q,              GLFW_KEY_Q             },
            {Keyboard::Key::R,              GLFW_KEY_R             },
            {Keyboard::Key::S,              GLFW_KEY_S             },
            {Keyboard::Key::T,              GLFW_KEY_T             },
            {Keyboard::Key::U,              GLFW_KEY_U             },
            {Keyboard::Key::V,              GLFW_KEY_V             },
            {Keyboard::Key::W,              GLFW_KEY_W             },
            {Keyboard::Key::X,              GLFW_KEY_X             },
            {Keyboard::Key::Y,              GLFW_KEY_Y             },
            {Keyboard::Key::Z,              GLFW_KEY_Z             },
            {Keyboard::Key::LeftBracket,    GLFW_KEY_LEFT_BRACKET  },
            {Keyboard::Key::Backslash,      GLFW_KEY_BACKSLASH     },
            {Keyboard::Key::RightBracket,   GLFW_KEY_RIGHT_BRACKET },
            {Keyboard::Key::GraveAccent,    GLFW_KEY_GRAVE_ACCENT  },
            {Keyboard::Key::World1,         GLFW_KEY_WORLD_1       },
            {Keyboard::Key::World2,         GLFW_KEY_WORLD_2       },
            {Keyboard::Key::Escape,         GLFW_KEY_ESCAPE        },
            {Keyboard::Key::Enter,          GLFW_KEY_ENTER         },
            {Keyboard::Key::Tab,            GLFW_KEY_TAB           },
            {Keyboard::Key::Backspace,      GLFW_KEY_BACKSPACE     },
            {Keyboard::Key::Insert,         GLFW_KEY_INSERT        },
            {Keyboard::Key::Delete,         GLFW_KEY_DELETE        },
            {Keyboard::Key::Right,          GLFW_KEY_RIGHT         },
            {Keyboard::Key::Left,           GLFW_KEY_LEFT          },
            {Keyboard::Key::Down,           GLFW_KEY_DOWN          },
            {Keyboard::Key::Up,             GLFW_KEY_UP            },
            {Keyboard::Key::PageUp,         GLFW_KEY_PAGE_UP       },
            {Keyboard::Key::PageDown,       GLFW_KEY_PAGE_DOWN     },
            {Keyboard::Key::Home,           GLFW_KEY_HOME          },
            {Keyboard::Key::End,            GLFW_KEY_END           },
            {Keyboard::Key::CapsLock,       GLFW_KEY_CAPS_LOCK     },
            {Keyboard::Key::ScrollLock,     GLFW_KEY_SCROLL_LOCK   },
            {Keyboard::Key::NumLock,        GLFW_KEY_NUM_LOCK      },
            {Keyboard::Key::PrintScreen,    GLFW_KEY_PRINT_SCREEN  },
            {Keyboard::Key::Pause,          GLFW_KEY_PAUSE         },
            {Keyboard::Key::F1,             GLFW_KEY_F1            },
            {Keyboard::Key::F2,             GLFW_KEY_F2            },
            {Keyboard::Key::F3,             GLFW_KEY_F3            },
            {Keyboard::Key::F4,             GLFW_KEY_F4            },
            {Keyboard::Key::F5,             GLFW_KEY_F5            },
            {Keyboard::Key::F6,             GLFW_KEY_F6            },
            {Keyboard::Key::F7,             GLFW_KEY_F7            },
            {Keyboard::Key::F8,             GLFW_KEY_F8            },
            {Keyboard::Key::F9,             GLFW_KEY_F9            },
            {Keyboard::Key::F10,            GLFW_KEY_F10           },
            {Keyboard::Key::F11,            GLFW_KEY_F11           },
            {Keyboard::Key::F12,            GLFW_KEY_F12           },
            {Keyboard::Key::F13,            GLFW_KEY_F13           },
            {Keyboard::Key::F14,            GLFW_KEY_F14           },
            {Keyboard::Key::F15,            GLFW_KEY_F15           },
            {Keyboard::Key::F16,            GLFW_KEY_F16           },
            {Keyboard::Key::F17,            GLFW_KEY_F17           },
            {Keyboard::Key::F18,            GLFW_KEY_F18           },
            {Keyboard::Key::F19,            GLFW_KEY_F19           },
            {Keyboard::Key::F20,            GLFW_KEY_F20           },
            {Keyboard::Key::F21,            GLFW_KEY_F21           },
            {Keyboard::Key::F22,            GLFW_KEY_F22           },
            {Keyboard::Key::F23,            GLFW_KEY_F23           },
            {Keyboard::Key::F24,            GLFW_KEY_F24           },
            {Keyboard::Key::F25,            GLFW_KEY_F25           },
            {Keyboard::Key::Num0,           GLFW_KEY_KP_0          },
            {Keyboard::Key::Num1,           GLFW_KEY_KP_1          },
            {Keyboard::Key::Num2,           GLFW_KEY_KP_2          },
            {Keyboard::Key::Num3,           GLFW_KEY_KP_3          },
            {Keyboard::Key::Num4,           GLFW_KEY_KP_4          },
            {Keyboard::Key::Num5,           GLFW_KEY_KP_5          },
            {Keyboard::Key::Num6,           GLFW_KEY_KP_6          },
            {Keyboard::Key::Num7,           GLFW_KEY_KP_7          },
            {Keyboard::Key::Num8,           GLFW_KEY_KP_8          },
            {Keyboard::Key::Num9,           GLFW_KEY_KP_9          },
            {Keyboard::Key::NumDecimal,     GLFW_KEY_KP_DECIMAL    },
            {Keyboard::Key::NumDivide,      GLFW_KEY_KP_DIVIDE     },
            {Keyboard::Key::NumMultiply,    GLFW_KEY_KP_MULTIPLY   },
            {Keyboard::Key::NumSubstract,   GLFW_KEY_KP_SUBTRACT   },
            {Keyboard::Key::NumAdd,         GLFW_KEY_KP_ADD        },
            {Keyboard::Key::NumEnter,       GLFW_KEY_KP_ENTER      },
            {Keyboard::Key::NumEqual,       GLFW_KEY_KP_EQUAL      },
            {Keyboard::Key::LeftShift,      GLFW_KEY_LEFT_SHIFT    },
            {Keyboard::Key::LeftControl,    GLFW_KEY_LEFT_CONTROL  },
            {Keyboard::Key::LeftAlt,        GLFW_KEY_LEFT_ALT      },
            {Keyboard::Key::LeftSuper,      GLFW_KEY_LEFT_SUPER    },
            {Keyboard::Key::RightShift,     GLFW_KEY_RIGHT_SHIFT   },
            {Keyboard::Key::RightControl,   GLFW_KEY_RIGHT_CONTROL },
            {Keyboard::Key::RightAlt,       GLFW_KEY_RIGHT_ALT     },
            {Keyboard::Key::RightSuper,     GLFW_KEY_RIGHT_SUPER   },
            {Keyboard::Key::Menu,           GLFW_KEY_MENU          }

    };

    std::unordered_map<int, Keyboard::Key> WindowsKeyboard::s_GlfwToKeyMap{};
    
    int ToGlfwKey(const Keyboard::Key& key)
    {
        return WindowsKeyboard::s_KeyToGlfwMap.at(key);
    }

    Keyboard::Key FromGlfwKey(int glfwKey)
    {
        if (WindowsKeyboard::s_GlfwToKeyMap.size() == 0)
            for (auto&& it : WindowsKeyboard::s_KeyToGlfwMap)
                WindowsKeyboard::s_GlfwToKeyMap[it.second] = it.first;
        return WindowsKeyboard::s_GlfwToKeyMap.at(glfwKey);
    }

    bool WindowsKeyboard::IsKeyPressedImpl(const Key& key) const
    {
        auto& window = Application::GetInstance().GetWindow();
        auto status = glfwGetKey(window.GetNativeHandle<GLFWwindow*>(), ToGlfwKey(key));
        return status == GLFW_PRESS || status == GLFW_REPEAT;
    }
}
