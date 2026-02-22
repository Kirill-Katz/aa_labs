#pragma once

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



