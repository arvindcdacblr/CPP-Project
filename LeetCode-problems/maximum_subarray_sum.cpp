#include <iostream>
#include <vector>
#include <tuple>

std::tuple<int, int, int> maxSubarraySum(const std::vector<int>& nums) {
    int maxSum = nums[0];
    int currentSum = nums[0];
    int start = 0, end = 0, tempStart = 0;

    for (size_t i = 1; i < nums.size(); ++i) {
        if (currentSum < 0) {
            currentSum = nums[i];
            tempStart = i;
        } else {
            currentSum += nums[i];
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = tempStart;
            end = i;
        }
    }

    return {maxSum, start, end};
}

int main() {
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    auto [maxSum, startIdx, endIdx] = maxSubarraySum(nums);

    std::cout << "Max Sum: " << maxSum << "\n";
    std::cout << "Subarray: ";
    for (int i = startIdx; i <= endIdx; ++i) {
        std::cout << nums[i] << " ";
    }
    std::cout << "\n";

    return 0;
}