
## 1. Extracting Messy Input
When the input contains "garbage" characters like `[` or `,`, the easiest way is to read the line and filter for what you want.

### For Numbers in `[1,2,3]` or `1,2,3`
This logic "collects" digits into a temporary string until it hits a non-digit (like a comma or bracket), then converts it.

```cpp
string s;
getline(cin, s);
vector<int> nums;
string temp = "";

for (char c : s) {
    if (isdigit(c) || c == '-') { // Handles negative numbers too
        temp += c;
    } else if (!temp.empty()) {
        nums.push_back(stoi(temp));
        temp = "";
    }
}
if (!temp.empty()) nums.push_back(stoi(temp)); // Don't forget the last one!
```

---

## 2. Binary Search: `lower_bound` vs `upper_bound`
These are used on **sorted** containers. They return an **iterator** (pointer-like object), so you usually subtract `v.begin()` to get the actual index.



* **`lower_bound`**: Finds the **first** element that is **$\ge$ target**.
* **`upper_bound`**: Finds the **first** element that is **$>$ target**.

| Target | Array | `lower_bound` index | `upper_bound` index |
| :--- | :--- | :--- | :--- |
| **3** | `[1, 2, 3, 3, 4]` | Index 2 (The first 3) | Index 4 (The 4) |
| **5** | `[1, 2, 3, 3, 4]` | Index 5 (`v.end()`) | Index 5 (`v.end()`) |

**Code Syntax:**
```cpp
auto it = lower_bound(v.begin(), v.end(), target);
int index = it - v.begin();

if (it != v.end()) {
    // Element found or an element larger than target exists
}
```

---

## 3. Finding Extreme Values: `max_element`
Like the bound functions, this returns an **iterator**. You must "dereference" it with an asterisk `*` to get the actual value.

```cpp
vector<int> v = {10, 50, 30, 70, 20};

// To get the VALUE
int maxVal = *max_element(v.begin(), v.end());

// To get the INDEX
int maxIdx = max_element(v.begin(), v.end()) - v.begin();
```

> **Note:** For finding the minimum, just use `min_element` exactly the same way.

---

## 4. The "Competitive Programming" Headers
If you want to stop memorizing which header goes where, just use these two lines at the top of every file.

```cpp
#include <bits/stdc++.h> // Includes everything (vector, map, algorithm, etc.)
using namespace std;

// Add inside main() for lightning-fast input/output
ios_base::sync_with_stdio(false);
cin.tie(NULL);
```

### Pro-Tip for your Notes:
When you use `max_element` or `sort` on an empty vector, your program will **crash**. Always ensure `!v.empty()` before calling these!

## 5. Integer / Double division

### 1. `(double)(a / b)` — **The "Too Late" Cast**
This is almost always a mistake if you are looking for a decimal.
* **What happens:** The computer divides integer `a` by integer `b` first. It chops off the decimal (truncates). **Then** it converts that whole number to a double.
* **Example:** `(double)(7 / 2)` $\rightarrow$ `(double)(3)` $\rightarrow$ `3.0`.
* **Result:** You lost your `.5` forever.

### 2. `(double)a / b` — **The "Right Way"**
This works perfectly.
* **What happens:** The cast is tied specifically to `a`. `a` becomes a double. In C++, if you divide a `double` by an `int`, the computer "promotes" the `int` to a `double` so it can do the math properly.
* **Example:** `(double)7 / 2` $\rightarrow$ `7.0 / 2` $\rightarrow$ `7.0 / 2.0` $\rightarrow$ `3.5`.
* **Result:** Correct decimal.

### 3. `a / (double)b` — **Also the "Right Way"**
This works for the exact same reason as #2.
* **What happens:** `b` becomes a double first. The computer sees `int / double` and promotes the numerator to a double to match.
* **Example:** `7 / (double)2` $\rightarrow$ `7 / 2.0` $\rightarrow$ `7.0 / 2.0` $\rightarrow$ `3.5`.
* **Result:** Correct decimal.

