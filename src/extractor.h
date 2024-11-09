// extractor.h
#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <filesystem>
#include <string>
#include <fstream>

// internal
#include "defines.h"

namespace fs = std::filesystem;

fs::path getDestinyName(fs::path originalPath);
uint8_t isAllowedExtension(const std::string& extension); // Agregar std:: antes de string
void registerNotCopiedFile(fs::path* notCopied, uint32_t& count, const fs::path& path);
void extractTracks(void);

#endif // EXTRACTOR_H