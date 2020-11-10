#ifndef FILE_DETECTION_Sets_H

#define FILE_DETECTION_Sets_H

#include <unordered_set>
#include <algorithm>

namespace FileDetection
{
    /*
    * Combine the set1 and set2
    * Return : The set which is the combination of set1 and set2
    */
    template<class T>
    std::unordered_set<T> sets_combine(const std::unordered_set<T>& set1,
        const std::unordered_set<T>& set2)
    {
        std::unordered_set<T> combined;

        combined.insert(set1.cbegin(), set1.cend());
        combined.insert(set2.cbegin(), set2.cend());

        return combined;
    }

    /*
    * Remove set2 data from set1
    * Return : set1 - set2
    */
    template<class T>
    std::unordered_set<T> set_substract(const std::unordered_set<T>& set1,
        const std::unordered_set<T>& set2)
    {
        std::unordered_set<T> differences_set;
      
        std::for_each(set1.cbegin(),
            set1.cend(),
            [&differences_set](const auto& data) {

                differences_set.insert(data);

            });

        
        std::for_each(set2.begin(),
            set2.end(),
            [&differences_set](auto& set2_data) {

                if (differences_set.size() > 0) {

                    auto found_iter = differences_set.find(set2_data);

                    //if set1 don't have data of set2
                    //we do not remove anything
                    if (found_iter == differences_set.end()) {
                        return;
                    }

                    differences_set.erase(found_iter);
                }
            });

        return differences_set;
    }
}

#endif