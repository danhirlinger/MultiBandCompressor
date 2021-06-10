/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   meter_37_frms_png;
    const int            meter_37_frms_pngSize = 54011;

    extern const char*   knob_05_128_png;
    const int            knob_05_128_pngSize = 881233;

    extern const char*   knob_05_256_png;
    const int            knob_05_256_pngSize = 1744396;

    extern const char*   knob_09_128_png;
    const int            knob_09_128_pngSize = 634758;

    extern const char*   knob_09_256_png;
    const int            knob_09_256_pngSize = 1249312;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
