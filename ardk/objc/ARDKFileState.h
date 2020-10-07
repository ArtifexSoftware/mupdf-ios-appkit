//
//  ARDKFileState.h
//  smart-office-nui
//
//  Created by Paul Gardiner on 10/01/2017.
//  Copyright © 2017 Artifex Software Inc. All rights reserved.
//

#import "ARDKLib.h"
#import <Foundation/Foundation.h>

@class ARDKDocSession;

@protocol ARDKFileState <NSObject>

/// The path to the document to display and edit
@property(readonly) NSString *absoluteInternalPath;

/// The file type
@property(readonly) ARDKDocType docType;

/// The path which will be displayed within the UI to
/// denote the file being edited. This may be different
/// to absoluteInternalPath for two reasons.
/// The app may be supplying the path to a copy of the
/// file in absoluteInternalPath, and wish to give a
/// displayPath that better represents the location of
/// the original file. Secondly, displayPath may use
/// a more readable start of path (e.g., "Storage/")
/// in place of the true location of the file
@property(readonly) NSString *displayPath;

/// Whether this file can be overwritten. If YES, saving
/// back of edits to the file are not permitted, and
/// the user will need to save to another location. An
/// app might return YES here for document templates.
@property(readonly) BOOL isReadonly;

/// In some use cases, an app may supply a copy of the file
/// to be edited, which will require copying back after any
/// edits have been saved. This property keeps track of
/// whether the original file is out of date with the
/// supplied one, and hence whether copying back may be needed.
/// For apps that supply the original file directly, this
/// property can simply return NO.
@property(readonly) BOOL requiresCopyBack;

/// Information regarding the viewing state of the file (e.g.,
/// which page is being viewed). The document view will ensure
/// this is valid when sessionDidClose is called. A class
/// implementing the ARDKFileState interface can record this
/// value (using its NSCoding interface) against the file name
/// and then arrange to restore it should the same file be
/// reopened.
@property(retain) NSObject<NSCoding> *viewingStateInfo;

/// Information method called when a session has loaded the
/// first page of the document
- (void)sessionDidLoadFirstPage:(ARDKDocSession *)session;

/// Information method called when the file is opened in the
/// main document view ready for viewing and editing by the user.
- (void)sessionDidShowDoc:(ARDKDocSession *)session;

/// Information method called when a session saves document
/// edits back to the supplied file
- (void)sessionDidSaveDoc:(ARDKDocSession *)session;

/// In some use cases, an app may supply a copy of the file
/// to be edited, which will require copying back after any
/// edits have been saved. This method will be called when
/// copying back may be necessary. For apps that supply the
/// original file directly, and return NO from requiresCopyBack
/// this method need do nothing.
- (void)sessionRequestedCopyBackOnCompletion:(void (^)(BOOL succeeded))block;

/// Information method called when a session ends. In the case
/// that an app supplies a copy of a file to be edited. This
/// method might delete the copy, since the session is no
/// longer using it. The file should NOT be copied back before
/// removal.
- (void)sessionDidClose;

@end
