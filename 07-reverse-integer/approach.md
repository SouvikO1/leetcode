![Runtime](https://img.shields.io/badge/Runtime-5%20ms%20(beats%2020.15%25)-orange?style=for-the-badge)
![Memory](https://img.shields.io/badge/Memory-8.49%20MB%20(beats%2084.38%25)-brightgreen?style=for-the-badge)

---

## Problem Explained

The goal is to take a signed (positive or negative) whole number `x` and reverse its digits. 

However, there is a catch. The result must fit inside a **32-bit signed integer** range. In plain terms, the answer must stay between **-2,147,483,648** (`INT_MIN`) and **2,147,483,647** (`INT_MAX`). If reversing the digits creates a number outside this range, you must return `0`.

You are also not allowed to store the number in a larger 64-bit integer container (like `long long` in C++) to catch the overflow easily. You must handle it using standard 32-bit integer limits.

**Examples:**
*   `123` becomes `321`.
*   `-123` becomes `-321`.
*   `120` becomes `21` (leading zeros naturally drop off).

---

## Intuition

To reverse a number, you peel off digits from the end one by one and build a new number.

1. **Peel the last digit:** You get the last digit of `x` using `x % 10`.
2. **Remove the last digit:** You drop the last digit from `x` using `x / 10`.
3. **Push the digit onto the new number:** You shift your reversed answer to the left by multiplying it by 10, then add the popped digit (`check * 10 + digit`).

**The Overflow Trick:**
Before multiplying your reversed answer by 10, you must ask: *will this step break the 32-bit limit?* 
* If `check` is already greater than `INT_MAX / 10` (which is `214,748,364`), multiplying by 10 will cause an **overflow** (going past the maximum limit).
* If `check` is less than `INT_MIN / 10` (which is `-214,748,364`), multiplying by 10 will cause an **underflow** (going below the minimum limit).

If either condition is met, return `0` immediately.

---

## Approach

Here is how the logic works step-by-step:

*   **Initialize a result tracker:** Set `check = 0` to hold the reversed number.
*   **Loop through the digits:** Keep running a loop as long as `x` is not equal to `0`.
*   **Check bounds before shifting:** Inside the loop, check if `check > INT_MAX / 10` or `check < INT_MIN / 10`. If either is true, return `0` right away to prevent illegal overflow.
*   **Append the digit:** Update `check` using `check = check * 10 + x % 10`. This extracts the last digit of `x` and attaches it to the right side of `check`.
*   **Shrink the input:** Divide `x` by `10` (`x /= 10`) to throw away the last digit you just processed.
*   **Return the answer:** When `x` reaches `0`, the loop ends. Return `check`.

---

## Time & Space Complexity

*   **Time Complexity:** **O(log10(|x|))** — Dividng `x` by 10 in every step reduces the number of digits by 1. Since a 32-bit integer has at most 10 digits, the loop runs a maximum of 10 times. This is effectively **O(1)** constant time.
*   **Space Complexity:** **O(1)** — The memory stays constant because you only use one integer variable (`check`) to store the output.

**Is this already optimal?**
Yes, this code is already at the theoretical best complexity. 

To reverse any number, you are forced to inspect every single digit at least once. Because a 32-bit integer never has more than 10 digits, both time and space performance are bounded and optimal. No algorithm can process digits without looking at them.

---

## Edge Cases Handled

*   **Negative Numbers:** In C++, the `%` operator keeps the negative sign for negative inputs (for example, `-123 % 10` gives `-3`). The math works seamlessly without extra `if` statements for signs.
*   **Numbers Ending in Zero:** Inputs like `120` yield digits `0`, `2`, then `1`. The expression `0 * 10 + 2` correctly produces `2`, dropping the leading zero automatically.
*   **Overflowing Reversals:** A valid 32-bit number like `1,534,236,469` reverses to `9,646,324,351`, which exceeds `INT_MAX`. The safeguard check catches this mid-loop and safely returns `0`.
*   **Single Digit and Zero:** Inputs like `0` or `7` exit immediately or finish in one pass, returning `0` or `7` cleanly.
