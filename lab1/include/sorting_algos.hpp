#pragma once

#include <algorithm>
#include <climits>
#include <vector>
#include <assert.h>
#include <span>

inline void merge_sort(std::span<int> src) {
    std::vector<int> ans(src.size());

    auto merge = [&](auto&& self, std::span<int> arr_span, std::span<int> tmp_span) {
        assert(arr_span.size() == tmp_span.size());
        if (arr_span.size() <= 1) {
            return;
        }

        size_t mid = arr_span.size() / 2;

        auto left_tmp = tmp_span.first(mid);
        auto left_arr = arr_span.first(mid);

        auto right_tmp = tmp_span.subspan(mid);
        auto right_arr = arr_span.subspan(mid);

        self(self, left_arr, left_tmp);
        self(self, right_arr, right_tmp);

        int l = 0, r = 0;
        while (l < left_arr.size() && r < right_arr.size()) {
            if (left_arr[l] < right_arr[r]) {
                tmp_span[l + r] = left_arr[l];
                l++;
            } else {
                tmp_span[l + r] = right_arr[r];
                r++;
            }
        }

        while (l < left_arr.size()) {
            tmp_span[l+r] = left_arr[l];
            l++;
        }

        while (r < right_arr.size()) {
            tmp_span[l+r] = right_arr[r];
            r++;
        }

        for (int i = 0; i < tmp_span.size(); ++i) {
            arr_span[i] = tmp_span[i];
        }
    };

    merge(merge, src, { ans.data(), ans.size() });
}

inline void quick_sort(std::span<int> src) {
    auto quick = [&](auto&& self, std::span<int> arr) {
        size_t n = arr.size();
        if (n <= 1) return;

        int left = 0, pivot = n / 2, right = arr.size()-1;
        if (arr[left] > arr[pivot]) std::swap(arr[pivot], arr[left]);
        if (arr[left] > arr[right]) std::swap(arr[left], arr[right]);
        if (arr[pivot] > arr[right]) std::swap(arr[pivot], arr[right]);

        std::swap(arr[pivot], arr[n-1]);
        int pivot_val = arr[n-1];

        size_t i = 0;
        for (int j = 0; j <= n - 2; ++j) {
            if (arr[j] < pivot_val) {
                std::swap(arr[i], arr[j]);
                i++;
            }
        }

        std::swap(arr[i], arr[n - 1]);

        self(self, { arr.data(), i + 1 });
        self(self, { arr.data() + i + 1, arr.size() - (i + 1) });
    };

    quick(quick, src);
}

inline void propagate_down(std::span<int> src, int j) {
    size_t n = src.size();
    while (true) {
        int left = j * 2 + 1;
        int right = j * 2 + 2;
        int largest = j;

        if (left < n && src[left] > src[largest]) {
            largest = left;
        }

        if (right < n && src[right] > src[largest]) {
            largest = right;
        }

        if (largest == j) break;
        std::swap(src[largest], src[j]);
        j = largest;
    }
}

inline void heapify(std::span<int> src) {
    size_t n = src.size();

    for (int i = n/2 - 1; i >= 0; --i) {
        propagate_down(src, i);
    }
}

inline void heap_sort(std::span<int> src) {
    size_t n = src.size();

    heapify(src);

    for (size_t end = n - 1; end > 0; --end) {
        std::swap(src[0], src[end]);
        propagate_down({ src.data(), end }, 0);
    }
}

inline void radix_sort_positive(std::span<int> src) {
    if (!src.size()) return;

    size_t n = src.size();
    int max_val = src[0];
    for (int i = 1; i < n; ++i) {
        max_val = std::max(src[i], max_val);
    }

    std::vector<int> tmp(n);
    auto get_digit = [](int n, int exp) {
        return (n / exp) % 10;
    };

    auto count_sort = [&](std::span<int> src, int exp) {
        size_t n = src.size();
        std::array<int, 10> count;
        count.fill(0);
        std::array<int, 10> pref;
        pref.fill(0);

        for (size_t i = 0; i < n; ++i) {
            count[get_digit(src[i], exp)]++;
        }

        pref[0] = 0;
        for (size_t i = 1; i < 10; ++i) {
            pref[i] = pref[i-1] + count[i-1];
        }

        for (size_t i = 0; i < n; ++i) {
            int pos = pref[get_digit(src[i], exp)]++;
            tmp[pos] = src[i];
        }

        std::ranges::copy(tmp, src.begin());
    };

    int exp = 1;
    while (max_val / exp > 0) {
        count_sort(src, exp);
        exp *= 10;
    }
}

inline void radix_sort(std::span<int> src) {
    std::vector<int> positive;
    std::vector<int> negative;

    for (int i = 0; i < src.size(); ++i) {
        if (src[i] >= 0) {
            positive.push_back(src[i]);
        } else {
            negative.push_back(abs(src[i]));
        }
    }

    radix_sort_positive({ positive.data(), positive.size() });
    radix_sort_positive({ negative.data(), negative.size() });

    for (size_t i = negative.size(); i-- > 0;) {
        src[negative.size() - i - 1] = -negative[i];
    }

    int offset = negative.size();
    for (int i = 0; i < positive.size(); ++i) {
        src[offset + i] = positive[i];
    }
}


