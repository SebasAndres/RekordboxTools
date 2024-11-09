// extractor.h
#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <string>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

// internal
#include "defines.h"

fs::path getDestinyName(fs::path originalPath);
uint8_t isAllowedExtension(const std::string& extension); // Agregar std:: antes de string
void registerNotCopiedFile(fs::path* notCopied, uint32_t& count, const fs::path& path);
void extractTracks(fs::path& src, fs::path& destiny);

#endif // EXTRACTOR_H