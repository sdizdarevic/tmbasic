#pragma once

#include "common.h"
#include "Object.h"
#include "ProcedureArtifact.h"

namespace vm {

class Procedure : public Object {
   public:
    bool isSystemProcedure;
    std::optional<std::string> source;
    std::optional<std::unique_ptr<ProcedureArtifact>> artifact;

    virtual Kind getKind() const;
    virtual std::size_t getHash() const;
    virtual bool equals(const Object& other) const;
};

}  // namespace vm
