#ifndef FILE_DETECTION_UNORDERED_INSERTER_H

#define FILE_DETECTION_UNORDERED_INSERTER_H

namespace FileDetection
{
    template<typename Container>
    class unordered_inserter {
    public:
        using iterator_category = std::output_iterator_tag;
        using value_type = void;
        using reference_type = void;
        using difference_type = void;
        using pointer = void;
        using reference = void;
        using container_type = Container;

        unordered_inserter& operator++() { return *this; } //no-op
        unordered_inserter& operator++(int) { return *this; } //no-op
        unordered_inserter& operator*() { return *this; } //no-op
        constexpr unordered_inserter& operator=(const typename Container::value_type& value) {
            container->insert(value);
            return *this;
        }
        constexpr unordered_inserter& operator=(typename Container::value_type&& value) {
            container->insert(std::move(value));
            return *this;
        }
        unordered_inserter(Container* container)
            : container(container)
        {}
    protected:
        Container* container;
    };
}
#endif