#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include <vector>

template <typename T, typename F_SIZE, typename F_BY>
inline void bucketsort(std::vector<T> &list, size_t maxNum, F_SIZE size, F_BY by) {
	size_t maxLen = 0;
	for (auto &el : list) {
		size_t s = size(el);
		if (s > maxLen) {
			maxLen = s;
		}
	}
	for (size_t i = 0; i < maxLen; i++) {
		std::vector<std::vector<T>> buckets(maxNum + 1); // 0 = empty word
		for (auto &el : list) {
			buckets[by(el, i) + 1].push_back(el);
		}
		size_t index = 0;
		for (auto bucket : buckets) {
			for (auto element : bucket) {
				list[index++] = element;
			}
		}
	}
}

#endif