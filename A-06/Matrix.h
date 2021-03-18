#pragma once
#include <memory>
#include <unordered_map>
#include <optional>

template <typename ElementType, ElementType ElementsDefaultValue, std::size_t DimensionsNum = 2, typename Allocator = std::allocator<ElementType>>
class Matrix 
{
public:

	using LowerDimensionMatrixType = Matrix<ElementType, ElementsDefaultValue, DimensionsNum - 1, Allocator>;
	using MatricesStorageType = std::unordered_map<std::size_t,
		LowerDimensionMatrixType,
		std::hash<std::size_t>,
		std::equal_to<std::size_t>,
		typename std::allocator_traits<Allocator>::template rebind_alloc<std::pair<const std::size_t, LowerDimensionMatrixType>>
	>;

	Matrix& operator=(const Matrix& Other)
	{
		this->LowerDimensionMatrices = Other.GetLowerDimensionMatrices();
		return *this;
	}

	// @todo: matrix wrapper?
	LowerDimensionMatrixType& operator[](const size_t Index)
	{
		return LowerDimensionMatrices[Index];
	}

	MatricesStorageType& GetLowerDimensionMatrices()
	{
		return LowerDimensionMatrices;
	}

	const MatricesStorageType& GetLowerDimensionMatrices() const
	{
		return LowerDimensionMatrices;
	}
	
private:
	MatricesStorageType LowerDimensionMatrices;
};

/* Partial specialization to stop recursion. */
template <typename ElementType, ElementType ElementsDefaultValue, typename Allocator>
class Matrix<ElementType, ElementsDefaultValue, 1, Allocator>
{
public:
	class ValueWrapper;
	using MatrixType = Matrix< ElementType, ElementsDefaultValue, 0, Allocator>;
	using ValuesStorageType = std::unordered_map<std::size_t,
		ValueWrapper,
		std::hash<std::size_t>,
		std::equal_to<std::size_t>,
		typename std::allocator_traits<Allocator>::template rebind_alloc<std::pair<const std::size_t, ValueWrapper>>
	>;
	
	Matrix() = default;

	ValueWrapper operator[](const size_t Index)
	{
		auto value = Values.find(Index);
		if (value != Values.end())
		{
			return value->second;
		}

		return ValueWrapper{ Index, Values };
	}
	
	class ValueWrapper
	{
	public:
		ValueWrapper() = delete;
		ValueWrapper(const size_t Val, ValuesStorageType& vPtr) : Index(Val), MyRef(vPtr) {}
		~ValueWrapper() = default;

		
		ValueWrapper& operator=(ValueWrapper Other)
		{
			if (this == &Other)
			{
				return *this;
			}
			
			this->Value = Other->GetValue();
			this->Index = Other.Index;
			this->MyRef = Other.MyRef;
			return *this;
		}

		operator ElementType() const
		{
			return Value;
		}

		ElementType& GetValue()
		{
			return Value;
		}

		ValueWrapper& operator=(const ElementType& InValue)
		{
			this->Value = InValue;

			auto wrapper = MyRef.find(Index);
			if (wrapper == MyRef.end())
			{
				MyRef.emplace(Index, *this);
			}
			
			return *this;
		}

	
		ElementType Value = ElementsDefaultValue;
		size_t Index = 0;
		ValuesStorageType& MyRef;
	};
	
private:
	
	ValuesStorageType Values;
};
