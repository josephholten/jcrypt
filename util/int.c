struct Int {
  char* data;
  u64 len;
};

// out = a + b
char Int_add(Int* out, Int* a, Int* b) {
  assert(a.len == b.len && out.len == a.len);
  u64 len = a.len;

  char c = 0;
  for (u64 i = 0; i < len; i++) {
    short sum = a.data[i] + b.data[i] + c;
    char* psum = (char*)&sum;
    out.data[i] = psum[0];
    c = psum[1];
  }
  
  return c;
}

// out += a, returning carry
Int_iadd(Int* out, Int* a) {
  char c = 0;
  for (u64 i = 0; i < a.len; i++) {
    short sum = a.data[i] + b.data[i] + c;
    char* psum = (char*)&sum;
    out.data[i] = psum[0];
    c = psum[1];
  }
  return c;
}


