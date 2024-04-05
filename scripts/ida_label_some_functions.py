# Run inside IDA, uses args given to GFReportPrefixedPrintf to automatically
# name functions that call it

import idaapi

seen_strings = set()
ea = get_name_ea_simple("GFReportPrefixedPrintf")
if ea != BADADDR:
    for ref in CodeRefsTo(ea, 1):
        instr = DecodePreviousInstruction(ref)
        for _ in range(3):
            instr = DecodePreviousInstruction(instr.ea)
        str_addr = instr.Op1.value
        str_val = get_strlit_contents(str_addr, -1, STRTYPE_C)
        if str_val is None:
            continue
        if str_val in seen_strings:
            continue
        seen_strings.add(str_val)
        str_val = (
            str_val.decode("utf8").replace("`", "").replace("-", "_").replace("'", "")
        )
        orig_name = get_func_name(instr.ea)
        ea = get_name_ea(0, orig_name)
        set_name(ea, str_val)

# idaapi.get_arg_addrs()
