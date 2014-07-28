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
        rpath = [[bundle resourcePath] UTF8String] + std::string("/");
    }

    [pool drain];

    return rpath;
}

// Get path of all car textures
std::vector<std::string> carPaths(void)
{
    // Fetch files
    NSString* carPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/Cars"];
    NSMutableArray* contents = [[[NSFileManager defaultManager] contentsOfDirectoryAtPath:carPath error:nil] mutableCopy];
    
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