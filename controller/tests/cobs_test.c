#include <stdio.h>

#include "inc/smartsensor/cobs.h"

// TODO(rqou): There isn't a proper way to compile these tests!

int cobs_encode_basic(void) {
  uint8_t cobs_in[] = {0x01, 0x11, 0x21, 0x31};
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len + 2];
  cobs_out[in_len + 2 - 1] = 0xAA;
  uint8_t cobs_out_correct[] = {0x05, 0x01, 0x11, 0x21, 0x31};

  size_t out_len = cobs_encode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len + 2 - 1] != 0xAA) return 1;
  if (out_len != in_len + 1) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_encode_empty(void) {
  uint8_t cobs_out[2];
  cobs_out[1] = 0xAA;

  size_t out_len = cobs_encode(cobs_out, NULL, 0);

  if (cobs_out[1] != 0xAA) return 1;
  if (out_len != 1) return 1;
  if (cobs_out[0] != 0x01) return 1;
  return 0;
}

int cobs_encode_onlyzero(void) {
  uint8_t cobs_in[] = {0x00};
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len + 2];
  cobs_out[in_len + 2 - 1] = 0xAA;
  uint8_t cobs_out_correct[] = {0x01, 0x01};

  size_t out_len = cobs_encode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len + 2 - 1] != 0xAA) return 1;
  if (out_len != in_len + 1) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_encode_withzero(void) {
  uint8_t cobs_in[] = {0x11, 0x22, 0x00, 0x33};
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len + 2];
  cobs_out[in_len + 2 - 1] = 0xAA;
  uint8_t cobs_out_correct[] = {0x03, 0x11, 0x22, 0x02, 0x33};

  size_t out_len = cobs_encode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len + 2 - 1] != 0xAA) return 1;
  if (out_len != in_len + 1) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_encode_multizero(void) {
  uint8_t cobs_in[] = {0x11, 0x00, 0x00, 0x33};
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len + 2];
  cobs_out[in_len + 2 - 1] = 0xAA;
  uint8_t cobs_out_correct[] = {0x02, 0x11, 0x01, 0x02, 0x33};

  size_t out_len = cobs_encode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len + 2 - 1] != 0xAA) return 1;
  if (out_len != in_len + 1) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_encode_reallylong(void) {
  uint8_t cobs_in[] = {
          0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
    0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
    0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
    0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
    0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
    0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
  };
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len + 3];
  cobs_out[in_len + 3 - 1] = 0xAA;
  uint8_t cobs_out_correct[] = {
    0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
    0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
    0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
    0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
    0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
    0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE,
    0x02, 0xFF,
  };

  size_t out_len = cobs_encode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len + 3 - 1] != 0xAA) return 1;
  if (out_len != in_len + 2) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_decode_basic(void) {
  uint8_t cobs_in[] = {0x05, 0x01, 0x11, 0x21, 0x31};
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len];
  cobs_out[in_len - 1] = 0xAA;
  uint8_t cobs_out_correct[] = {0x01, 0x11, 0x21, 0x31};

  size_t out_len = cobs_decode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len - 1] != 0xAA) return 1;
  if (out_len != in_len - 1) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_decode_empty(void) {
  uint8_t cobs_out[1];
  cobs_out[0] = 0xAA;

  size_t out_len = cobs_decode(cobs_out, NULL, 0);

  if (cobs_out[0] != 0xAA) return 1;
  if (out_len != 0) return 1;
  return 0;
}

int cobs_decode_emptyout(void) {
  uint8_t cobs_in[] = {0x01};
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len];
  cobs_out[in_len - 1] = 0xAA;

  size_t out_len = cobs_decode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len - 1] != 0xAA) return 1;
  if (out_len != in_len - 1) return 1;
  return 0;
}

int cobs_decode_onlyzero(void) {
  uint8_t cobs_in[] = {0x01, 0x01};
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len];
  cobs_out[in_len - 1] = 0xAA;
  uint8_t cobs_out_correct[] = {0x00};

  size_t out_len = cobs_decode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len - 1] != 0xAA) return 1;
  if (out_len != in_len - 1) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_decode_withzero(void) {
  uint8_t cobs_in[] = {0x03, 0x11, 0x22, 0x02, 0x33};
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len];
  cobs_out[in_len - 1] = 0xAA;
  uint8_t cobs_out_correct[] = {0x11, 0x22, 0x00, 0x33};

  size_t out_len = cobs_decode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len - 1] != 0xAA) return 1;
  if (out_len != in_len - 1) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_decode_multizero(void) {
  uint8_t cobs_in[] = {0x02, 0x11, 0x01, 0x02, 0x33};
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len];
  cobs_out[in_len - 1] = 0xAA;
  uint8_t cobs_out_correct[] = {0x11, 0x00, 0x00, 0x33};

  size_t out_len = cobs_decode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len - 1] != 0xAA) return 1;
  if (out_len != in_len - 1) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_decode_reallylong(void) {
  uint8_t cobs_in[] = {
    0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
    0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
    0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
    0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
    0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
    0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE,
    0x02, 0xFF,
  };
  size_t in_len = sizeof(cobs_in);
  uint8_t cobs_out[in_len - 1];
  cobs_out[in_len - 2] = 0xAA;
  uint8_t cobs_out_correct[] = {
          0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
    0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
    0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
    0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
    0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
    0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
  };

  size_t out_len = cobs_decode(cobs_out, cobs_in, in_len);

  if (cobs_out[in_len - 2] != 0xAA) return 1;
  if (out_len != in_len - 2) return 1;
  return memcmp(cobs_out, cobs_out_correct, out_len);
}

int cobs_stream_basic(void) {
  cobs_decode_state state;
  memset(&state, 0, sizeof(state));

  if (cobs_decode_stream(&state, 0x05) != COBS_STREAM_DUMMY) return 1;
  if (cobs_decode_stream(&state, 0x01) != 0x01) return 1;
  if (cobs_decode_stream(&state, 0x11) != 0x11) return 1;
  if (cobs_decode_stream(&state, 0x21) != 0x21) return 1;
  if (cobs_decode_stream(&state, 0x31) != 0x31) return 1;
  if (cobs_decode_stream(&state, COBS_STREAM_END) != COBS_STREAM_END) return 1;
  // We need this in order to be ready to decode more data.
  if (state.current_block_len != 0) return 1;
  if (state.initial != 0) return 1;
  return 0;
}

int cobs_stream_empty(void) {
  cobs_decode_state state;
  memset(&state, 0, sizeof(state));

  if (cobs_decode_stream(&state, COBS_STREAM_END) != COBS_STREAM_END) return 1;
  // We need this in order to be ready to decode more data.
  if (state.current_block_len != 0) return 1;
  if (state.initial != 0) return 1;
  return 0;
}

int cobs_stream_emptyout(void) {
  cobs_decode_state state;
  memset(&state, 0, sizeof(state));

  if (cobs_decode_stream(&state, 0x01) != COBS_STREAM_DUMMY) return 1;
  if (cobs_decode_stream(&state, COBS_STREAM_END) != COBS_STREAM_END) return 1;
  // We need this in order to be ready to decode more data.
  if (state.current_block_len != 0) return 1;
  if (state.initial != 0) return 1;
  return 0;
}

int cobs_stream_onlyzero(void) {
  cobs_decode_state state;
  memset(&state, 0, sizeof(state));

  if (cobs_decode_stream(&state, 0x01) != COBS_STREAM_DUMMY) return 1;
  if (cobs_decode_stream(&state, 0x01) != 0x00) return 1;
  if (cobs_decode_stream(&state, COBS_STREAM_END) != COBS_STREAM_END) return 1;
  // We need this in order to be ready to decode more data.
  if (state.current_block_len != 0) return 1;
  if (state.initial != 0) return 1;
  return 0;
}

int cobs_stream_withzero(void) {
  cobs_decode_state state;
  memset(&state, 0, sizeof(state));

  if (cobs_decode_stream(&state, 0x03) != COBS_STREAM_DUMMY) return 1;
  if (cobs_decode_stream(&state, 0x11) != 0x11) return 1;
  if (cobs_decode_stream(&state, 0x22) != 0x22) return 1;
  if (cobs_decode_stream(&state, 0x02) != 0x00) return 1;
  if (cobs_decode_stream(&state, 0x33) != 0x33) return 1;
  if (cobs_decode_stream(&state, COBS_STREAM_END) != COBS_STREAM_END) return 1;
  // We need this in order to be ready to decode more data.
  if (state.current_block_len != 0) return 1;
  if (state.initial != 0) return 1;
  return 0;
}

int cobs_stream_multizero(void) {
  cobs_decode_state state;
  memset(&state, 0, sizeof(state));

  if (cobs_decode_stream(&state, 0x02) != COBS_STREAM_DUMMY) return 1;
  if (cobs_decode_stream(&state, 0x11) != 0x11) return 1;
  if (cobs_decode_stream(&state, 0x01) != 0x00) return 1;
  if (cobs_decode_stream(&state, 0x02) != 0x00) return 1;
  if (cobs_decode_stream(&state, 0x33) != 0x33) return 1;
  if (cobs_decode_stream(&state, COBS_STREAM_END) != COBS_STREAM_END) return 1;
  // We need this in order to be ready to decode more data.
  if (state.current_block_len != 0) return 1;
  if (state.initial != 0) return 1;
  return 0;
}

int cobs_stream_reallylong(void) {
  cobs_decode_state state;
  memset(&state, 0, sizeof(state));

  if (cobs_decode_stream(&state, 0xFF) != COBS_STREAM_DUMMY) return 1;
  for (uint8_t i = 0x01; i <= 0xFE; i++) {
    if (cobs_decode_stream(&state, i) != i) return 1;
  }
  if (cobs_decode_stream(&state, 0x02) != COBS_STREAM_DUMMY) return 1;
  if (cobs_decode_stream(&state, 0xFF) != 0xFF) return 1;
  if (cobs_decode_stream(&state, COBS_STREAM_END) != COBS_STREAM_END) return 1;
  // We need this in order to be ready to decode more data.
  if (state.current_block_len != 0) return 1;
  if (state.initial != 0) return 1;
  return 0;
}

#define run_test(X) {                                       \
  int ret = X();                                            \
  if (ret != 0) {                                           \
    failures++;                                             \
    fprintf(stderr, "Test %s FAILED!\n", #X);               \
  } else {                                                  \
    printf("Test %s passed.\n", #X);                        \
  }                                                         \
}
int main(int argc, char **argv) {
  int failures = 0;

  run_test(cobs_encode_basic);
  run_test(cobs_encode_empty);
  run_test(cobs_encode_onlyzero);
  run_test(cobs_encode_withzero);
  run_test(cobs_encode_multizero);
  run_test(cobs_encode_reallylong);

  run_test(cobs_decode_basic);
  run_test(cobs_decode_empty);
  run_test(cobs_decode_emptyout);
  run_test(cobs_decode_onlyzero);
  run_test(cobs_decode_withzero);
  run_test(cobs_decode_multizero);
  run_test(cobs_decode_reallylong);

  run_test(cobs_stream_basic);
  run_test(cobs_stream_empty);
  run_test(cobs_stream_emptyout);
  run_test(cobs_stream_onlyzero);
  run_test(cobs_stream_multizero);
  run_test(cobs_stream_reallylong);

  return failures;
}
