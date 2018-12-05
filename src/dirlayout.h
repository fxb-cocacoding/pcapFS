#ifndef PCAPFS_FILESYSTEM_H
#define PCAPFS_FILESYSTEM_H

#include <cstdint>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "index.h"
#include "commontypes.h"


namespace pcapfs_filesystem {

    typedef std::map<std::string, pcapfs::FilePtr> FileIndexMap;

    typedef struct DirTreeNode {
        std::string dirname;
        DirTreeNode *parent;
        std::map<std::string, struct DirTreeNode *> subdirs;
        FileIndexMap dirfiles;
        pcapfs::TimePoint timestamp = pcapfs::TimePoint::min();
        pcapfs::TimePoint timestampOldest = pcapfs::TimePoint::max();
    } DirTreeNode;


    extern pcapfs::Index index;


    class DirectoryLayout {
    public:
        static int initFilesystem(pcapfs::Index &index, std::string sortby);

        static DirTreeNode *findDirectory(const std::vector<std::string> &path_v);

        static pcapfs::FilePtr findFile(std::string path);

        static std::vector<std::string> pathVector(std::string path);

    private:
        static DirTreeNode *ROOT;
        static std::vector<std::string> dirSortby;

        static int fillDirTreeSortby(pcapfs::Index &index);

        static DirTreeNode *getOrCreateSubdir(DirTreeNode *current, const std::string &dirname);

        static void initRoot();

    };

}

#endif //PCAPFS_FILESYSTEM_H
