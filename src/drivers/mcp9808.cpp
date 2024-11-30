#include "mcp9808.hpp"

#include <cstdint>
constexpr static uint8_t address = 0x18;
using REGISTER_E = enum : uint8_t {
    REGISTER_UNUSED = 0x00,
    REGISTER_CONFIG,
    REGISTER_TUPPER,
    REGISTER_TLOWER,
    REGISTER_TCRIT,
    REGISTER_AMBIENTEMP,
    REGISTER_MFGID,
    REGISTER_DEVICEID,
    REGISTER_RESOLUTION,
    REGISTER_COUNT
};
using RESOLUTION_E = enum : uint8_t {
    RESOLUTION_0C5 = 0x00,
    RESOLUTION_0C25,
    RESOLUTION_0C125,
    RESOLUTION_0C0625,
    RESOLUTION_CCOUNT,
};

using T_HYST_E = enum : uint8_t {
    HYST_0C = 0x00,
    HYST_1C5 = 0x01,
    HYST_3C = 0x02,
    HYST_6C = 0x03,
};

union cfgReg {
    uint16_t blob;
    using Register = struct {
        unsigned unused0 : 5;
        unsigned tHyst : 2;
        unsigned shdn : 1;
        unsigned critLock : 1;
        unsigned winLock : 1;
        unsigned intClear : 1;
        unsigned alertStat : 1;
        unsigned alertCnt : 1;
        unsigned alertSel : 1;
        unsigned AlertPol : 1;
        unsigned AlertMod : 1;
    };
};

union limitTemp {
    uint16_t blob;
    using Register = struct {
        unsigned unused0 : 3;
        signed temperature : 11;
        signed unused1 : 2;
    };
    using RegisterDetailed = struct {
        unsigned unused0 : 3;
        unsigned sign : 1;
        unsigned temperature : 8;
        unsigned decimal : 2;
        signed unused1 : 2;
    };
};

union ambientTemp {
    uint16_t blob;
    using Register = struct {
        unsigned tType : 1;
        unsigned tUpper : 1;
        unsigned tLower : 1;
        signed temperature : 13;
    };
    using Register_Detailed = struct {
        unsigned tType : 1;
        unsigned tUpper : 1;
        unsigned tLower : 1;
        unsigned sign : 1;
        unsigned temperature : 8;
        unsigned decimal : 4;
    };
};
