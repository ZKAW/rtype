#pragma once

#include "ecs/Registry.hpp"
#include "ecs/components/allComponents.hpp"
#include "ecs/systems/allSystems.hpp"
#include "entity/allEntities.hpp"
#include "packet_types_generated.h"
#include <filesystem>

struct Snapshot {
    SparseArray<component::Position> positions;
    SparseArray<component::Drawable> drawables;
};

class SnapshotPacket {
  public:
    static flatbuffers::Offset<fbs::SnapshotPacket>
    create(flatbuffers::FlatBufferBuilder &builder,
           const SparseArray<component::Position> &positionsArray,
           const SparseArray<component::Drawable> &drawablesArray)
    {
        auto positionsOffset = serializePositions(builder, positionsArray);
        auto drawablesOffset = serializeDrawables(builder, drawablesArray);

        auto snap = fbs::CreateSnapshotPacket(builder, positionsOffset,
                                              drawablesOffset);
        return snap;
    }

    static std::unique_ptr<Snapshot>
    unpack(const fbs::SnapshotPacket *snapshotPacket)
    {
        auto snapshot = std::make_unique<Snapshot>();
        unpackPositions(snapshotPacket->positions(), snapshot->positions);
        unpackDrawables(snapshotPacket->drawables(), snapshot->drawables);
        return snapshot;
    }

  private:
    static flatbuffers::Offset<
        flatbuffers::Vector<flatbuffers::Offset<fbs::Position>>>
    serializePositions(flatbuffers::FlatBufferBuilder &builder,
                       const SparseArray<component::Position> &positionsArray)
    {
        std::vector<flatbuffers::Offset<fbs::Position>> positionOffsets;
        for (auto &&[id, pos] : IndexedZipper(positionsArray)) {
            positionOffsets.push_back(
                fbs::CreatePosition(builder, id, pos.x, pos.y));
        }
        return builder.CreateVector(positionOffsets);
    }

    static flatbuffers::Offset<
        flatbuffers::Vector<flatbuffers::Offset<fbs::DrawableInfo>>>
    serializeDrawables(flatbuffers::FlatBufferBuilder &builder,
                       const SparseArray<component::Drawable> &drawablesArray)
    {
        std::vector<flatbuffers::Offset<fbs::DrawableInfo>> drawableOffsets;
        for (auto &&[id, drawable] : IndexedZipper(drawablesArray)) {
            auto currentAnimationOffset =
                builder.CreateString(drawable.currentAnimation);
            auto nextAnimationOffset =
                builder.CreateString(drawable.nextAnimation);

            std::vector<flatbuffers::Offset<fbs::AnimationEntry>>
                animationEntries;
            for (const auto &[key, anim] : drawable.animations) {
                auto keyOffset = builder.CreateString(key);
                auto textureOffset = builder.CreateString(anim.texture);
                auto srcRect =
                    fbs::CreateRect(builder, anim.srcRect.x, anim.srcRect.y,
                                    anim.srcRect.w, anim.srcRect.h);
                auto destRect =
                    fbs::CreateRect(builder, anim.destRect.x, anim.destRect.y,
                                    anim.destRect.w, anim.destRect.h);
                auto animOffset = fbs::CreateAnimation(
                    builder, textureOffset, anim.xOrigin, srcRect, destRect,
                    anim.frameCount, anim.frameWidth, anim.frameDuration,
                    anim.loop, anim.leftToRight, anim.currentFrame,
                    anim.elapsedTime);
                /* std::cout << "Anim key: " << key << std::endl; */
                /* std::cout << "Anim texture: " << anim.texture << std::endl;
                 */
                animationEntries.push_back(
                    fbs::CreateAnimationEntry(builder, keyOffset, animOffset));
            }
            auto animationsOffset = builder.CreateVector(animationEntries);

            drawableOffsets.push_back(fbs::CreateDrawableInfo(
                builder, id, currentAnimationOffset, nextAnimationOffset,
                animationsOffset, drawable.zIndex));
        }
        return builder.CreateVector(drawableOffsets);
    }

    static void unpackPositions(
        const flatbuffers::Vector<flatbuffers::Offset<fbs::Position>>
            *positions,
        SparseArray<component::Position> &positionsArray) {
        positionsArray = SparseArray<component::Position>();
        for (const auto &pos : *positions) {
            positionsArray.insert_at(pos->entity_id(),
                                     component::Position{pos->x(), pos->y()});
            // std::cout << "Unpacked position for entity " << pos->entity_id()
            //           << ": " << pos->x() << ", " << pos->y() << std::endl;
        }
    }

    static void unpackDrawables(
        const flatbuffers::Vector<flatbuffers::Offset<fbs::DrawableInfo>>
            *drawables,
        SparseArray<component::Drawable> &drawablesArray) {
        drawablesArray = SparseArray<component::Drawable>();
        for (const auto &drawableInfo : *drawables) {
            size_t entityId = drawableInfo->entity_id();
            std::string currentAnimation =
                drawableInfo->current_animation()->str();
            std::string nextAnimation = drawableInfo->next_animation()->str();

            std::map<std::string, component::Animation> animations;
            for (const auto &animEntry : *drawableInfo->animations()) {
                std::string key = animEntry->key()->str();
                const auto &anim = animEntry->value();
                animations[key] = component::Animation{
                    .texture = anim->texture()->str(),
                    .xOrigin = anim->x_origin(),
                    .srcRect = {anim->src_rect()->x(), anim->src_rect()->y(),
                                anim->src_rect()->w(), anim->src_rect()->h()},
                    .destRect = {anim->dest_rect()->x(), anim->dest_rect()->y(),
                                 anim->dest_rect()->w(),
                                 anim->dest_rect()->h()},
                    .frameCount = anim->frame_count(),
                    .frameWidth = anim->frame_width(),
                    .frameDuration = anim->frame_duration(),
                    .loop = anim->loop(),
                    .leftToRight = anim->left_to_right(),
                    .currentFrame = anim->current_frame(),
                    .elapsedTime = anim->elapsed_time()
                };
            }

            drawablesArray.insert_at(
                entityId,
                component::Drawable{.currentAnimation = currentAnimation,
                                    .nextAnimation = nextAnimation,
                                    .animations = animations,
                                    .zIndex = drawableInfo->z_index()});
        }
    }
};
