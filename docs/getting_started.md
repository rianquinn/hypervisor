# Getting Started

This is C++ code
``` cpp
template<template<typename> typename INTERFACE, typename DETAILS>
class bfpair : public INTERFACE<bfpair<INTERFACE, DETAILS>>
{
    using details_type = DETAILS;
    using interface_type = INTERFACE<bfpair<INTERFACE, DETAILS>>;

private:
    constexpr static auto
    details(interface_type *i) -> DETAILS &
    {
        return static_cast<bfpair<INTERFACE, DETAILS> *>(i)->d;
    }

    constexpr static auto
    details(const interface_type *i) -> const DETAILS &
    {
        return static_cast<const bfpair<INTERFACE, DETAILS> *>(i)->d;
    }

private:
    DETAILS d;
    friend class INTERFACE<bfpair<INTERFACE, DETAILS>>;
};

```
