//
//  RaygunClient.h
//  raygun4apple
//
//  Created by Mitchell Duncan on 27/08/18.
//  Copyright © 2018 Raygun Limited. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall remain in place
// in this source code.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#import <Foundation/Foundation.h>
#import "RaygunDefines.h"

@class RaygunUserInformation, RaygunMessage, RaygunBreadcrumb;

NS_ASSUME_NONNULL_BEGIN

@interface RaygunClient : NSObject

@property (nonatomic, class) enum RaygunLoggingLevel logLevel;

@property (nonatomic, class, readonly, copy) NSString *apiKey;

@property (nullable, nonatomic, copy) NSString *applicationVersion;

@property (nullable, nonatomic, strong) NSArray *tags;

@property (nullable, nonatomic, strong) NSDictionary<NSString *, id> *customData;

@property (nullable, nonatomic, strong) RaygunUserInformation *userInformation;

@property (nonatomic, copy) RaygunBeforeSendMessage beforeSendMessage;

@property (nonatomic, assign) int maxReportsStoredOnDevice;

@property (nonatomic, readonly, copy) NSArray<RaygunBreadcrumb *> *breadcrumbs;

+ (instancetype)sharedInstance;

+ (instancetype)sharedInstanceWithApiKey:(NSString *)apiKey
NS_SWIFT_NAME(sharedInstance(apiKey:));

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithApiKey:(NSString *)apiKey NS_DESIGNATED_INITIALIZER;

// Crash Reporting

- (void)enableCrashReporting;

- (void)sendException:(NSException *)exception;

- (void)sendException:(NSException *)exception
             withTags:(nullable NSArray *)tags
NS_SWIFT_NAME(sendException(exception:tags:));

- (void)sendException:(NSException *)exception
             withTags:(nullable NSArray *)tags
       withCustomData:(nullable NSDictionary *)customData
NS_SWIFT_NAME(sendException(exception:tags:customData:));

- (void)sendException:(NSString *)exceptionName
           withReason:(nullable NSString *)reason
             withTags:(nullable NSArray *)tags
       withCustomData:(nullable NSDictionary *)customData
NS_SWIFT_NAME(sendException(name:reason:tags:customData:));

- (void)sendError:(NSError *)error
         withTags:(nullable NSArray *)tags
   withCustomData:(nullable NSDictionary *)customData
NS_SWIFT_NAME(sendError(error:tags:customData:));

- (void)sendMessage:(RaygunMessage *)message;

- (void)recordBreadcrumb:(RaygunBreadcrumb *)breadcrumb;

- (void)recordBreadcrumbWithMessage:(NSString *)message
                       withCategory:(nullable NSString *)category
                          withLevel:(enum RaygunBreadcrumbLevel)level
                     withCustomData:(nullable NSDictionary *)customData
NS_SWIFT_NAME(recordBreadcrumb(message:category:level:customData:));

- (void)clearBreadcrumbs;

// Real User Monitoring (RUM)

- (void)enableRealUserMonitoring;

- (void)enableNetworkPerformanceMonitoring;

- (void)ignoreViews:(NSArray *)viewNames;

- (void)ignoreURLs:(NSArray *)urls;

- (void)sendTimingEvent:(enum RaygunEventTimingType)type
               withName:(NSString *)name
           withDuration:(int)milliseconds
NS_SWIFT_NAME(sendTimingEvent(type:name:duration:));

@end

NS_ASSUME_NONNULL_END
