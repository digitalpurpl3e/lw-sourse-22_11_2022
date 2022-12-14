#pragma once

#include <windows.h>

inline BYTE logotyperaw[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x0F, 0x08, 0x06, 0x00, 0x00, 0x00, 0x47, 0xB0, 0x89,
0x93, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B,
0x13, 0x01, 0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00, 0x00, 0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xAE,
0xCE, 0x1C, 0xE9, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41, 0x4D, 0x41, 0x00, 0x00, 0xB1, 0x8F, 0x0B,
0xFC, 0x61, 0x05, 0x00, 0x00, 0x02, 0x8F, 0x49, 0x44, 0x41, 0x54, 0x78, 0x01, 0xE5, 0x58, 0xEF,
0x55, 0xDB, 0x40, 0x0C, 0x97, 0xFB, 0xF2, 0xBD, 0xDE, 0xA0, 0x97, 0x09, 0x4A, 0x27, 0xC0, 0x4C,
0x50, 0x3A, 0x01, 0xDE, 0x80, 0x6E, 0x90, 0x64, 0x82, 0xB2, 0x41, 0x60, 0x02, 0x60, 0x02, 0xBB,
0x13, 0x24, 0x9D, 0xC0, 0x66, 0x82, 0xB8, 0x13, 0x08, 0x29, 0x3E, 0xC3, 0x45, 0xD6, 0xDD, 0xD9,
0x07, 0x8F, 0x2F, 0xFC, 0xDE, 0xD3, 0x33, 0xE8, 0x24, 0x59, 0xA7, 0xD3, 0x9F, 0x73, 0x32, 0x08,
0x00, 0x11, 0xCF, 0xE8, 0x71, 0x26, 0xF9, 0x59, 0x96, 0xDD, 0x06, 0x74, 0x72, 0x7A, 0x5C, 0xC2,
0x3C, 0xB4, 0x4C, 0x64, 0xB7, 0x15, 0xB6, 0xD8, 0x4E, 0x0E, 0xF3, 0xF1, 0x40, 0xB6, 0x3A, 0xC5,
0xA7, 0x6F, 0x44, 0xC6, 0xF3, 0xFE, 0x7F, 0x44, 0x7B, 0xE9, 0x83, 0x17, 0x64, 0xD4, 0x10, 0x35,
0xA8, 0xE3, 0x2A, 0xA2, 0x97, 0x8A, 0x8A, 0xF5, 0x1D, 0x5B, 0x0D, 0xA6, 0xE1, 0x7C, 0x08, 0x0C,
0xD1, 0x16, 0xE7, 0x61, 0x47, 0x54, 0x4C, 0x09, 0xD0, 0x3A, 0x60, 0xE4, 0x80, 0xFD, 0xA9, 0xBC,
0x77, 0x80, 0x4E, 0x6C, 0xE3, 0xDB, 0x03, 0xB4, 0xC3, 0x74, 0x14, 0x6C, 0x63, 0xE1, 0xDB, 0x24,
0x3D, 0x64, 0x96, 0xEC, 0xE1, 0xB5, 0xDC, 0x78, 0x03, 0xD7, 0x44, 0x1B, 0x98, 0x86, 0x5B, 0x0F,
0x3F, 0xB7, 0x36, 0x8D, 0xE0, 0xFD, 0x24, 0xBA, 0x53, 0xE4, 0x1F, 0x88, 0x3A, 0x88, 0xA3, 0xB3,
0x1B, 0x94, 0xED, 0xE1, 0x86, 0xA8, 0x26, 0x7A, 0x22, 0x3A, 0xD8, 0xF7, 0x0E, 0xE5, 0x57, 0x0A,
0xD9, 0x95, 0x95, 0x1D, 0x03, 0xC7, 0xD9, 0xB3, 0xE5, 0x17, 0x0A, 0x9E, 0x9A, 0x45, 0xA8, 0x64,
0x10, 0x04, 0x80, 0x7D, 0x19, 0x48, 0x5C, 0xD9, 0xB5, 0x46, 0xF0, 0xCF, 0x61, 0x22, 0x48, 0xB6,
0x54, 0xEC, 0xE6, 0x01, 0xF9, 0xDF, 0xD8, 0x97, 0xF8, 0x0B, 0x31, 0x7F, 0xA1, 0x6D, 0x10, 0xC6,
0xD9, 0xB3, 0xE1, 0xE6, 0x45, 0x6B, 0x35, 0xFD, 0x5D, 0x58, 0xDE, 0xDC, 0x2C, 0xF2, 0x41, 0x73,
0xFA, 0xAF, 0x47, 0xF6, 0x92, 0x7C, 0x58, 0x42, 0x04, 0x76, 0x88, 0xB4, 0xCA, 0x12, 0x97, 0x1C,
0x57, 0xC2, 0x5E, 0xF0, 0x3B, 0x2B, 0xCF, 0xFB, 0xAC, 0x21, 0x04, 0x2D, 0x7B, 0x9C, 0xB5, 0x68,
0x16, 0xA1, 0xDE, 0x83, 0xAA, 0x00, 0x1D, 0x84, 0xBD, 0x6B, 0xC7, 0x56, 0x83, 0x09, 0x70, 0xF4,
0x2B, 0x9C, 0x0F, 0xF6, 0x61, 0x8B, 0xCE, 0xB0, 0x90, 0x9B, 0x6B, 0x84, 0x82, 0x11, 0x32, 0x95,
0x58, 0xFF, 0x33, 0x21, 0x40, 0x53, 0x71, 0x8F, 0xEF, 0x30, 0xC5, 0x1C, 0xFD, 0x94, 0x29, 0x36,
0x60, 0xC7, 0x36, 0x32, 0x99, 0x3D, 0xD0, 0x37, 0xA7, 0x01, 0x2D, 0x8C, 0x1B, 0x2C, 0x37, 0x3E,
0x79, 0xCF, 0x59, 0x0E, 0xF7, 0x07, 0xBB, 0xC1, 0x06, 0xD2, 0xD1, 0x12, 0xFD, 0xE0, 0x7B, 0x0C,
0x07, 0x08, 0x4E, 0x1B, 0x38, 0x97, 0x46, 0xB4, 0x49, 0x93, 0xEE, 0x85, 0xFB, 0x3F, 0xF6, 0x59,
0xFE, 0x1D, 0x7A, 0xDF, 0x87, 0x8C, 0x37, 0xF6, 0x99, 0x5B, 0x2A, 0x14, 0x53, 0x17, 0x99, 0x63,
0x84, 0x15, 0x2A, 0xD0, 0x2F, 0x52, 0x31, 0xD4, 0x83, 0x53, 0x9E, 0x00, 0x15, 0x1E, 0x3D, 0x76,
0xAC, 0x84, 0x71, 0xC0, 0x4B, 0xB2, 0x77, 0xA7, 0x04, 0xA8, 0x20, 0xBE, 0xAF, 0x3F, 0x9D, 0x00,
0xFB, 0x46, 0x5F, 0x3A, 0xAC, 0x8E, 0x74, 0x7F, 0x05, 0xE4, 0x0D, 0x8C, 0xFD, 0x2E, 0xDD, 0x26,
0x5D, 0x42, 0x5A, 0x70, 0x18, 0xDC, 0x9B, 0x0A, 0x5F, 0x83, 0x8B, 0x6C, 0xEA, 0x91, 0x74, 0x79,
0xE4, 0xBA, 0xBD, 0xCC, 0x78, 0x64, 0xB9, 0x7C, 0x9F, 0x20, 0x8E, 0x0E, 0x94, 0xAC, 0xE0, 0x0A,
0x21, 0x5F, 0xD6, 0x30, 0x1D, 0x5D, 0x66, 0x15, 0x0D, 0x8C, 0xB3, 0x67, 0x1D, 0x51, 0xE6, 0x53,
0x77, 0xEF, 0x19, 0xC7, 0x2C, 0xD2, 0x4E, 0x82, 0xF8, 0x59, 0xC8, 0x10, 0xF6, 0x23, 0xB5, 0x70,
0xDF, 0x4D, 0x2A, 0x1B, 0x25, 0x83, 0xA6, 0xA2, 0x24, 0x7A, 0xB4, 0x7E, 0xC8, 0x29, 0xD9, 0x3A,
0x34, 0x40, 0xFD, 0xA4, 0x22, 0x2C, 0x17, 0x8E, 0x41, 0xE3, 0x2C, 0xF0, 0xB7, 0x4C, 0x70, 0x7C,
0x93, 0xF3, 0x9C, 0x15, 0x95, 0xC3, 0x3A, 0x66, 0x11, 0xE8, 0xE3, 0xF5, 0xC3, 0x61, 0x7B, 0x18,
0x97, 0xFD, 0x3D, 0x9C, 0xEE, 0xCD, 0xC0, 0xB4, 0xA0, 0x73, 0x99, 0xB7, 0x5F, 0xEC, 0x89, 0xAF,
0xC4, 0xE2, 0x4D, 0x4C, 0xDB, 0x96, 0x53, 0x2D, 0xD8, 0x2B, 0x48, 0x83, 0x6C, 0xBC, 0x29, 0x1F,
0xA8, 0x23, 0x90, 0x8F, 0xDC, 0xD4, 0x39, 0x48, 0xBC, 0x9F, 0xFD, 0x04, 0x95, 0xD6, 0xCA, 0xF2,
0xD0, 0x39, 0xDE, 0xE4, 0x33, 0xF8, 0x44, 0xB0, 0xD3, 0xCC, 0x10, 0x7D, 0x15, 0x4B, 0x2D, 0xD1,
0x7F, 0xF7, 0x17, 0x80, 0x01, 0xCF, 0xBD, 0xF8, 0xC6, 0x58, 0x9C, 0x2B, 0x4A, 0x8A, 0x00, 0x00,
0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, };