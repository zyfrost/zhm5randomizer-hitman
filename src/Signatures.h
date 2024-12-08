#ifndef __ZHM5RANDOMIZER_SRC_SIGNATURES_H__
#define __ZHM5RANDOMIZER_SRC_SIGNATURES_H__s
#include <string>
#include <unordered_map>
#include <vector>

namespace Signatures {

// Locates a memory region based on a unique byte signature and an offset from the start of the signature.
struct Locator {
    std::vector<int16_t> signature;
    int32_t offset;
};

// Map of names locators
extern std::unordered_map<std::string, Locator> locators;

}; // namespace Signatures

#endif // __ZHM5RANDOMIZER_SRC_SIGNATURES_H__

// // Signatures.h

// #include <unordered_map>
// #include <vector>

// namespace Signatures {

// struct Locator {
//     std::vector<int> pattern;
//     int offset;
// };

// extern std::unordered_map<std::string, Locator> locators;

// }  // namespace Signatures
