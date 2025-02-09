// Sha384Reg.cpp /TR 2018-11-02

#include "StdAfx.h"

#include "../../C/CpuArch.h"

EXTERN_C_BEGIN
#include "../../Codecs/hashes/sha.h"
EXTERN_C_END

#include "../Common/MyCom.h"
#include "../7zip/Common/RegisterCodec.h"

#include "../../C/7zVersion.h"
#if MY_VER_MAJOR >= 23
#define MY_UNKNOWN_IMP1 Z7_COM_UNKNOWN_IMP_1
#endif

// SHA384
class CSHA384Hasher:
  public IHasher,
  public CMyUnknownImp
{
  SHA384_CTX _ctx;

public:
  CSHA384Hasher() { SHA384_Init(&_ctx); }

  MY_UNKNOWN_IMP1(IHasher)
#if MY_VER_MAJOR >= 23
  Z7_IFACE_COM7_IMP(IHasher)
#else
  INTERFACE_IHasher(;)
#endif

public:
  virtual ~CSHA384Hasher() = default;
};

STDMETHODIMP_(void) CSHA384Hasher::Init() throw()
{
  SHA384_Init(&_ctx);
}

STDMETHODIMP_(void) CSHA384Hasher::Update(const void *data, UInt32 size) throw()
{
  SHA384_Update(&_ctx, (const Byte *)data, size);
}

STDMETHODIMP_(void) CSHA384Hasher::Final(Byte *digest) throw()
{
  SHA384_Final(digest, &_ctx);
}
REGISTER_HASHER(CSHA384Hasher, 0x208, "SHA384", SHA384_DIGEST_LENGTH)
