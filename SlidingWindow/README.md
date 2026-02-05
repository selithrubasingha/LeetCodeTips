## Best Time to Buy and Sell Stock

- You basically need to Buy the stock at the lowest point in the array . and Sell it at the highest point in the array while traversing from left to right . 

1. While traversing through the array , maintain a variable storing the current minimum value .
2. while traversing through the array with r pointer , if the the value at the index in larger than the min , check if it's larger than the max . if so update the max

```python
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        l, r = 0, 1
        maxP = 0

        while r < len(prices):
            if prices[l] < prices[r]:
                profit = prices[r] - prices[l]
                maxP = max(maxP, profit)
            else:
                l = r
            r += 1
        return maxP
```