#include "Error.h"
#include "../util/win.h"

namespace vm {

Error::Error(ErrorCode code, const std::string& message) : code(code), std::runtime_error(message) {}

Error Error::fromDirectoryErrno(int posixError, const std::string& path) {
    switch (posixError) {
        case ENOENT:
            return Error(ErrorCode::kFileNotFound, fmt::format("The directory \"{}\" does not exist.", path));
        case EACCES:
            return Error(ErrorCode::kAccessDenied, fmt::format("Access to the directory \"{}\" was denied.", path));
        case ENAMETOOLONG:
            return Error(ErrorCode::kPathTooLong, fmt::format("The path \"{}\" is too long.", path));
        case ENOSPC:
            return Error(
                ErrorCode::kDiskFull, fmt::format("The disk containing the directory \"{}\" is out of space.", path));
        case ENOTDIR:
            return Error(ErrorCode::kPathIsNotDirectory, fmt::format("The path \"{}\" is not a directory.", path));
        case EEXIST:
        case ENOTEMPTY:
            return Error(ErrorCode::kDirectoryNotEmpty, fmt::format("The directory \"{}\" is not empty.", path));
        default:
            return Error(
                ErrorCode::kIoFailure,
                fmt::format("Failed to access the directory \"{}\". {}", path, strerror(posixError)));
    }
}

Error Error::fromDirectoryWinError(uint32_t winError, const std::string& path) {
    (void)winError;
    (void)path;
#ifdef _WIN32
    switch (winError) {
        case ERROR_FILE_NOT_FOUND:
        case ERROR_PATH_NOT_FOUND:
            return Error(ErrorCode::kFileNotFound, fmt::format("The directory \"{}\" does not exist.", path));
        case ERROR_ACCESS_DENIED:
            return Error(ErrorCode::kAccessDenied, fmt::format("Access to the directory \"{}\" was denied.", path));
        case ERROR_FILENAME_EXCED_RANGE:
            return Error(ErrorCode::kPathTooLong, fmt::format("The path \"{}\" is too long.", path));
        case ERROR_FILE_EXISTS:
        case ERROR_ALREADY_EXISTS:
            return Error(ErrorCode::kDirectoryNotEmpty, fmt::format("The directory \"{}\" is not empty.", path));
        default:
            return Error(
                ErrorCode::kIoFailure,
                fmt::format("Failed to access the directory \"{}\". {}", path, util::winFormatErrorMessage(winError)));
    }
#else
    throw std::runtime_error("Called Windows-specific function Error::fromDirectoryWinError() on non-Windows platform");
#endif
}

Error Error::fromFileErrno(int posixError, const std::string& filePath) {
    switch (posixError) {
        case ENOENT:
            return Error(ErrorCode::kFileNotFound, fmt::format("The file \"{}\" does not exist.", filePath));
        case EACCES:
            return Error(ErrorCode::kAccessDenied, fmt::format("Access to the file \"{}\" was denied.", filePath));
        case ENAMETOOLONG:
            return Error(ErrorCode::kPathTooLong, fmt::format("The path \"{}\" is too long.", filePath));
        case ENOSPC:
            return Error(
                ErrorCode::kDiskFull, fmt::format("The disk containing the file \"{}\" is out of space.", filePath));
        case EISDIR:
            return Error(ErrorCode::kPathIsDirectory, fmt::format("The path \"{}\" is a directory.", filePath));
        default:
            return Error(
                ErrorCode::kIoFailure,
                fmt::format("Failed to access the file \"{}\". {}", filePath, strerror(posixError)));
    }
}

}  // namespace vm
