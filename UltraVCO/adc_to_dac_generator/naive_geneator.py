values = {
    2099: 2149,
    2134: 2028,
    2169: 1915,
    2204: 1807,
    2240: 1705,
    2272: 1610,
    2308: 1519,
    2344: 1434,
    2377: 1535,
    2414: 1277,
    2447: 1206,
    2481: 1138,
    2515: 1077,
}

def find_closest_value(input):
    if input in values.keys():
        return values[input]
    else:
        error = 9999
        closest_key = -1
        for key in values.keys():
            if error > abs(key - input):
                error = abs(key - input)
                closest_key = key
        return values[closest_key]

naive_step = 8
header = "constexpr std::array<std::pair<int, int>, 4096> dac_values_and_steps = {{\n"
end = "}};\n"

with open("../src/adc_to_dac_and_step.hpp", "w") as o:
    o.write("#include <array>\n")
    o.write(header)
    for i in range(4096):
        #{0, 1},
        o.write("    {" + str(find_closest_value(i)) + ", " + str(naive_step) + "},\n")
    o.write(end)

