//
// Component to aid resource handling
// ResourcePath.mm
//

#include "ResourcePath.hpp"
#import <Foundation/Foundation.h>

// Get resource path
std::string resourcePath(void)
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    std::string rpath;
    NSBundle* bundle = [NSBundle mainBundle];

    if (bundle == nil) {
#ifdef DEBUG
        NSLog(@"bundle is nil... thus no resources path can be found.");
#endif
    } else {
        NSString* path = [bundle resourcePath];
        rpath = [path UTF8String] + std::string("/");
    }

    [pool drain];

    return rpath;
}

// Get path of all car textures
std::vector<std::string> carPaths(void)
{
    // Fetching path
    NSString* bundlePath = [[NSBundle mainBundle] resourcePath];
    NSString* carPath = [bundlePath stringByAppendingString:@"/Cars"];
    
    // Fetching files in the specific path
    NSFileManager* fileManager = [NSFileManager defaultManager];
    NSMutableArray* contents = [[fileManager contentsOfDirectoryAtPath:carPath error:nil] mutableCopy];
    
    // Remove non png
    for (NSString* fileName in [contents reverseObjectEnumerator]) {
        if (![fileName hasSuffix:@".png"]) {
            [contents removeObject:fileName];
        }
    }
    
    // Moving file names to C++ vector
    std::vector<std::string> results;
    for (NSString* fileName in contents) {
        results.push_back(std::string("Cars/") + [fileName UTF8String]);
    }
    return results;
}