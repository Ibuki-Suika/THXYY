#ifndef THGAMEOBJECT_H
#define THGAMEOBJECT_H

#include "../Common/THCommon.h"
#include <Math\THMath.h>
#include "../Tween/THTweenManager.h"

namespace THEngine
{
	class Layer;
	class RenderQueue;

	class GameObject : public EngineObject
	{
	protected:
		LinkedList<GameObject*> children;
		bool needRemove;

		Vector3f position = Vector3f(0.0f, 0.0f, 0.0f);
		Vector3f color = Vector3f(1.0f, 1.0f, 1.0f);
		float alpha = 1.0f;

		Vector3f scale = Vector3f(1.0f, 1.0f, 1.0f);

		Quaternion rotation3D;

		TweenManager* tweenManager = nullptr;

		Vector3f positionForRender = Vector3f(0.0f, 0.0f, 0.0f);

	private:
		void Visit();
		void PushDataStack();
		void PopDataStack();
		void WriteRenderData();

	protected:
		virtual void SendToRenderQueue();

	public:
		GameObject();
		GameObject(const GameObject& object);
		virtual ~GameObject();

		virtual void Update() override;
		virtual void Draw() override;

		virtual Object* Clone() override;
		
		virtual void OnDestroy();

		void AddChild(GameObject* obj);

		void RemoveChild(GameObject* child);

		void RemoveAllChildren();

		inline void MarkDestroy() { needRemove = true; }

		inline bool NeedRemove() { return needRemove; }
	

		void AddTween(Tween* tween);

		inline void KillTween(Tween* tween)
		{
			tweenManager->KillTween(tween);
		}

		inline void SetPosition(const Vector3f& position)
		{
			this->position = position;
			this->positionForRender = position;
		}

		inline const Vector3f& GetPosition()
		{
			return position;
		}

		inline void SetColor(const Vector3f& color)
		{
			this->color = color;
		}

		inline const Vector3f& GetColor()
		{
			return color;
		}

		inline float GetAlpha() { return alpha; }
		inline void SetAlpha(float alpha) { this->alpha = alpha; }

		inline void SetScale(Vector3f scale) { this->scale = scale; }
		inline Vector3f GetScale() { return scale; }

		void SetRotationByAxis(const Vector3f& axis, float rotation);

		friend class Layer;
		friend class RenderQueue;
		friend class MoveTo;
		friend class MoveBy;
		friend class FadeTo;
		friend class FadeOut;
		friend class ColorTo;
		friend class ScaleTo;
	};
}

#endif