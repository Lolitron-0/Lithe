#include "ltpch.h"
#include "Mouse.hpp"

namespace Lithe
{
    const std::unordered_map<Mouse::Button, std::string> Mouse::s_ButtonToStringMap
    {
            {Button::Button1,    "Button1"  },
            {Button::Button2,    "Button2"  },
            {Button::Button3,    "Button3"  },
            {Button::Button4,    "Button4"  },
            {Button::Button5,    "Button5"  },
            {Button::Button6,    "Button6"  },
            {Button::Button7,    "Button7"  },
            {Button::Button8,    "Button8"  },
            {Button::Left,       "LMB"      },
            {Button::Right,      "RMB"      },
            {Button::Middle,     "CMB"      }
    };

    std::string Mouse::ButtonToString(Button button)
    {
        return s_ButtonToStringMap.at(button);
    }
}