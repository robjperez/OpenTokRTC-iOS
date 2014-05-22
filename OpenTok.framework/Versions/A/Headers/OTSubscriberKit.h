//
//  OTSubscriberKit.h
//
//  Copyright (c) 2013 Tokbox, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenTok/OpenTokObjC.h>

@class OTStream, OTSession;

@protocol OTSubscriberKitDelegate;

/**
 * An OTSubscriberKit (subscriber) object renders media data bound to an
 * <OTStream>. The OTSubscriberKit class lets you set a custom video renderer
 * for the video stream. Use this class if you are interested in providing your
 * own video processing and rendering implementation. Otherwise, use the
 * OTSubscriber class, which includes a pre-built video processor and renderer.
 *
 * The stream property references the stream that you have subscribed to.
 * The OTSubscriberKit class includes methods that let you disable and enable
 * local audio and video playback for the subscribed stream.
 */

@interface OTSubscriberKit : NSObject

/** @name Getting basic information about a Subscriber */

/**
 * The <OTSession> object that owns this subscriber. An instance will have
 * one and only one <OTSession> associated with it, and this property
 * is immutable.
 */
@property(readonly) OTSession* session;

/**
 * The stream this subscriber is bound to. Any media channels
 * on the stream should be available for display/playback with
 * this instance.
 */
@property(readonly) OTStream* stream;

/**
 * The <OTSubscriberKitDelegate> object that serves as a delegate,
 * handling events for this OTSubscriber object.
 */
@property(nonatomic, assign) id<OTSubscriberKitDelegate> delegate;

/**
 * Whether to subscribe to the stream's audio.
 *
 * The default value is YES.
 *
 * Setting this property has no effect if the <[OTStream hasAudio]> property is set to NO.
 */
@property(nonatomic) BOOL subscribeToAudio;

/**
 * Whether to subscribe to the stream's video. Setting this property only has an affect if you do so immediately
 * after initializing the OTSubscriber object.
 *
 * The default value is YES.
 *
 * Setting this property has no effect if the <[OTStream hasVideo]> property is set to NO.
 */
@property(nonatomic) BOOL subscribeToVideo;

/**
 * The video renderer for this instance.
 */
@property(nonatomic, retain) id<OTVideoRender> videoRender;

/** @name Initializing a Subscriber */

/**
 * Initializes an OTSubscriber and binds it to an <OTStream> instance.
 * Once initialized, the instance is permanently bound to the stream.
 *
 * The OpenTok iOS SDK supports a limited number of simultaneous audio-video streams in an app:
 *
 * - On iPad 2 and iPad 3, the limit is four streams. An app can have up to four simultaneous subscribers,
 * or one publisher and up to three subscribers.
 * - On all other supported iOS devices, the limit is two streams. An app can have up to two subscribers,
 * or one publisher and one subscriber.
 *
 * Initializing an OTSubscriber causes it to start streaming data from the OpenTok server, regardless of whether
 * the view of the OTSubscriber object is added to a superview.
 *
 * You can stream audio only (without subscribing to the video stream) by setting the
 * <[OTSubscriberKit subscribeToVideo]> property to NO immediately after initializing the OTSubscriber object.
 * You can stream video only (without subscribing to the audio stream) by setting the
 * <[OTSubscriberKit subscribeToAudio]> property to NO immediately after initializing the
 * OTSubscriber object.
 *
 * When the subscriber connects to the stream, the <[OTSubscriberKitDelegate subscriberDidConnectToStream:]> message
 * is sent to the subscriber delegate. Then, when the first frame of video has been decoded, the
 * <[OTSubscriberKitDelegate subscriberVideoDataReceived:]> message is sent to the subscriber delegate.
 *
 * If the subscriber fails to connect to the stream, the <[OTSubscriberKitDelegate subscriber:didFailWithError:]>
 * message is sent to the subscriber delegate.
 *
 * @param stream The <OTStream> object to bind this instance to.
 * @param delegate The delegate (<OTSubscriberKitDelegate>) that will handle events generated by
 * this instance.
 */
- (id)initWithStream:(OTStream*)stream
            delegate:(id<OTSubscriberKitDelegate>)delegate;

@end

/**
 * Used to send messages for an OTSubscriber instance. When you send
 * the <[OTSubscriberKit initWithStream:delegate:]> message, you specify an
 * OTSubscriberKitDelegate object.
 */
@protocol OTSubscriberKitDelegate <NSObject>

/** @name Using subscribers */

/**
 * Sent when the subscriber successfully connects to the stream.
 * @param subscriber The subscriber that generated this event.
 */
- (void)subscriberDidConnectToStream:(OTSubscriberKit*)subscriber;

/**
 * Sent if the subscriber fails to connect to its stream.
 * @param subscriber The subscriber that generated this event.
 * @param error The error (an <OTError> object) that describes this connection error. The
 * `OTSubscriberErrorCode` enum (defined in the OTError class) defines values for the `code`
 * property of this object.
 */
- (void)subscriber:(OTSubscriberKit*)subscriber didFailWithError:(OTError*)error;

@optional

/**
 * Sent when the first frame of video has been decoded. Although the
 * subscriber will connect in a relatively short time, video can take
 * more time to synchronize. This message is sent after the
 * <subscriberDidConnectToStream> message is sent.
 * @param subscriber The subscriber that generated this event.
 */
- (void)subscriberVideoDataReceived:(OTSubscriberKit*)subscriber;

/**
 * Sent when the video dimensions of a stream changes. This occurs when a stream published from an iOS device resizes,
 * based on a change in the device orientation.
 *
 * This message is available for WebRTC only.
 *
 * @param stream The stream that changed video dimensions.
 * @param dimensions The new dimensions of the encoded stream.
 */
- (void)stream:(OTStream*)stream didChangeVideoDimensions:(CGSize)dimensions;

/**
 * This message is sent when the OpenTok media server stops sending video to the subscriber.
 * This feature of the OpenTok media server has a subscriber drop the video stream when connectivity degrades.
 * The subscriber continues to receive the audio stream, if there is one.
 *
 * @param subscriber The <OTSubscriber> that will no longer receive video.
 */
- (void)subscriberVideoDisabled:(OTSubscriberKit*)subscriber;

@end