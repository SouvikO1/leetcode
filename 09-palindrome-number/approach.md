![Runtime](https://img.shields.io/badge/Runtime-0%20ms%20(beats%20100.00%25)-brightgreen?style=for-the-badge)
![Memory](https://img.shields.io/badge/Memory-10.26%20MB%20(beats%2037.97%25)-orange?style=for-the-badge)

---

## Problem Explained

A **palindrome** is a number (or word) that reads the exact same forward and backward. 

Given an integer `x`, your job is to check if it is a palindrome:
* Return `true` if it reads the same from left to right and right to left.
* Return `false` if it does not.

### Examples
* **`x = 121`** $\rightarrow$ **`true`**: Reads as `121` from left to right and `121` from right to left.
* **`x = -121`** $\rightarrow$ **`false`**: Left to right is `-121`. Right to left is `121-`. The negative sign breaks it.
* **`x = 10`** $\rightarrow$ **`false`**: Right to left gives `01` (which is just `1`), not `10`.

---

## Intuition

The naive way to solve this is converting the number into a string and comparing characters from both ends. But that requires extra memory.

We can solve this purely with math:
* What if we reverse the number mathematically?
* Even better: **we only need to reverse the second half of the number.**

If we reverse the back half of the digits and it matches the front half, the number is a palindrome! 

**Why only half?**
1. Reversing the entire number can cause an **integer overflow** (the reversed number might be too big to fit in a standard 32-bit integer).
2. Once the reversed back half becomes equal to or larger than the remaining front half, we know we have reached the middle of the number.

---

## Approach

Here is the step-by-step logic using half-number reversal in C++:

```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        // Step 1: Filter out impossible cases
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int revertedNumber = 0;
        
        // Step 2: Reverse the second half of the digits
        while (x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }

        // Step 3: Compare front half (x) with reversed back half (revertedNumber)
        return x == revertedNumber || x == revertedNumber / 10;
    }
};
```

### Detailed Steps:
* **Rule out quick negatives & trailing zeros**: 
  * If `x` is negative, return `false` right away.
  * If `x` ends in `0` (and is not `0` itself), return `false`. A number cannot start with `0`.
* **Set up a variable**: 
  * Initialize `revertedNumber = 0` to hold the reversed back half.
* **Extract digits from the back**:
  * Run a loop while `x > revertedNumber`.
  * Use **modulo** (`x % 10`) to get the last digit (the remainder when dividing by 10).
  * Append this digit to `revertedNumber` by multiplying `revertedNumber` by 10 and adding the digit.
  * Chop the last digit off `x` using integer division (`x /= 10`).
* **Check if both halves match**:
  * For numbers with an **even** number of digits (like `1221`), `x` will equal `revertedNumber` (e.g., `12 == 12`).
  * For numbers with an **odd** number of digits (like `12321`), `revertedNumber` will hold `321` and `x` will hold `12`. We discard the middle digit (`3`) using `revertedNumber / 10` and compare (`12 == 12`).

---

## Time & Space Complexity

* **Time:** **O(log₁₀ n)** — In each step of the loop, we divide the input by 10. The number of iterations equals half the number of digits in `x`. Since standard integers have at most 10 digits, this loop runs at most 5 times, making it effectively **O(1)** in practice.
* **Space:** **O(1)** — We only use one extra integer variable (`revertedNumber`). No strings, arrays, or extra memory are allocated.

### Is this optimal?
**Yes, this is the most optimal possible solution.** 
* It achieves linear time relative to the number of digits while using zero extra memory.
* By stopping halfway, it avoids 32-bit integer overflow entirely, making it safer and faster than reversing the whole number.

---

## Edge Cases Handled

* **Negative Numbers (e.g., `-121`)**: Caught immediately by `x < 0`. Returns `false`.
* **Numbers ending in zero (e.g., `10`, `100`)**: Caught by `x % 10 == 0 && x != 0`. Returns `false`.
* **Single-digit numbers (e.g., `0`, `7`)**: 
  * `0` skips the check and returns `true`.
  * Single digits like `7` run through the loop once (`x` becomes `0`, `revertedNumber` becomes `7`). The check `0 == 7 / 10` evaluates to `0 == 0`, returning `true`.
* **Even vs. Odd Digit Lengths (e.g., `1221` vs `121`)**: Correctly handled by checking both `x == revertedNumber` and `x == revertedNumber / 10`.
* **32-Bit Integer Overflow**: Prevented by design, because `revertedNumber` never grows larger than `x`.
