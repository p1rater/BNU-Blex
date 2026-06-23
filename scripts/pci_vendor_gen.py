#!/usr/bin/env python3
"""
pci_vendor_gen.py – Generate compact C vendor lookup table from pci.ids
"""

import sys

def parse_pci_ids(path):
    vendors = []
    with open(path, 'r', errors='replace') as f:
        for line in f:
            line = line.rstrip('\n\r')
            if not line or line.startswith('#') or line.startswith('\t'):
                continue
            parts = line.split(None, 1)
            if len(parts) < 2:
                continue
            vid_str, name = parts[0], parts[1]
            if len(vid_str) != 4:
                continue
            try:
                vid = int(vid_str, 16)
            except ValueError:
                continue
            vendors.append((vid, name))
    return vendors

def escape_c_string(s):
    result = []
    for c in s:
        if c == '"':
            result.append('\\"')
        elif c == '\\':
            result.append('\\\\')
        elif 32 <= ord(c) < 127:
            result.append(c)
        else:
            result.append('\\x{:02x}'.format(ord(c)))
    return ''.join(result)

def generate(vendors, out_h, out_c):
    vendors.sort(key=lambda x: x[0])
    n = len(vendors)

    # Build string table
    name_table = []
    entries = []
    offset = 0
    for vid, name in vendors:
        name_table.append(name)
        entries.append((vid, offset))
        offset += len(name.encode('utf-8')) + 1

    # Header
    with open(out_h, 'w') as f:
        f.write('/* pci_vendors.h – auto-generated from pci.ids */\n')
        f.write('#ifndef PCI_VENDORS_H\n#define PCI_VENDORS_H\n')
        f.write('#include <stdint.h>\n')
        f.write('#define PCI_VENDOR_MAX %d\n\n' % n)
        f.write('const char* pci_vendor_name(uint16_t vendor_id);\n')
        f.write('int pci_vendor_count(void);\n')
        f.write('#endif\n')

    # C source
    with open(out_c, 'w') as f:
        f.write('/* pci_vendors.c – auto-generated from pci.ids (%d vendors) */\n' % n)
        f.write('#include "pci_vendors.h"\n\n')

        # String table
        f.write('static const char vendor_names[] =\n')
        for i, name in enumerate(name_table):
            esc = escape_c_string(name)
            f.write('    "%s\\n"\n' % esc)
        f.write('    ;\n\n')

        # Lookup table
        f.write('static const struct {\n')
        f.write('    uint16_t id;\n')
        f.write('    uint16_t name_off;\n')
        f.write('} vendor_table[%d] = {\n' % n)
        for i, (vid, off) in enumerate(entries):
            sep = ',' if i < n - 1 else ' '
            f.write('    { 0x%04X, %5d }%s\n' % (vid, off, sep))
        f.write('};\n\n')

        # Binary search
        f.write('const char* pci_vendor_name(uint16_t vendor_id) {\n')
        f.write('    int lo = 0, hi = %d - 1;\n' % n)
        f.write('    while (lo <= hi) {\n')
        f.write('        int mid = lo + (hi - lo) / 2;\n')
        f.write('        if (vendor_table[mid].id == vendor_id)\n')
        f.write('            return &vendor_names[vendor_table[mid].name_off];\n')
        f.write('        if (vendor_table[mid].id < vendor_id)\n')
        f.write('            lo = mid + 1;\n')
        f.write('        else\n')
        f.write('            hi = mid - 1;\n')
        f.write('    }\n')
        f.write('    return (const char*)0;\n')
        f.write('}\n\n')
        f.write('int pci_vendor_count(void) { return %d; }\n' % n)

if __name__ == '__main__':
    pci_ids_path = sys.argv[1] if len(sys.argv) > 1 else 'pci.ids'
    out_h = sys.argv[2] if len(sys.argv) > 2 else 'drivers/pci_vendors.h'
    out_c = sys.argv[3] if len(sys.argv) > 3 else 'drivers/pci_vendors.c'
    vendors = parse_pci_ids(pci_ids_path)
    print("Parsed %d vendors from %s" % (len(vendors), pci_ids_path))
    generate(vendors, out_h, out_c)
    print("Generated %s and %s" % (out_h, out_c))
