#include "../IStorage.h"
#include <string>
#include <unordered_map>

class TestStorageFactory : public IStorageFactory
{
    virtual class IStorage *create(int db, key_load_iterator itr, void *privdata) override;
    virtual class IStorage *createMetadataDb() override;
    virtual const char *name() const override;
    virtual size_t totalDiskspaceUsed() const override { return 0; }
    virtual bool FSlow() const override { return false; }
};

class TestStorageProvider final : public IStorage
{
    std::unordered_map<std::string, std::string> m_map;
    std::unordered_map<std::string, std::string>::iterator m_iter = m_map.end();

public:
    TestStorageProvider();
    virtual ~TestStorageProvider();

    virtual void insert(const char *key, size_t cchKey, void *data, size_t cb, bool fHintOverwrite) override;
    virtual bool erase(const char *key, size_t cchKey) override;
    virtual void retrieve(const char *key, size_t cchKey, callbackSingle fn) const override;
    virtual size_t clear() override;
    virtual bool enumerate(callback fn) const override;
    virtual size_t stateful_enumerate(callback fn) override;
    virtual size_t count() const override;

    virtual void flush() override;

    /* This is permitted to be a shallow clone */
    virtual const IStorage *clone() const override;
};
